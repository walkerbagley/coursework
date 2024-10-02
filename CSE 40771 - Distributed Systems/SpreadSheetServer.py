import socket
import sys
import json
import SpreadSheet
from datetime import date
import time
import os

class Request():
    def __init__(self, method: str, args) -> None:
        self.method = method
        self.args = args
        self.request = {'method': method.lower(), 'args': args}
    
    def __str__(self) -> str:
        return(json.dumps(self.request))

class LogEntry():
    def __init__(self, request: Request) -> None:
        self.request = request
    
    def __str__(self) -> str:
        return json.dumps({'timestamp': time.time(), 'request': self.request.request})

class Response():
    def __init__(self, status: int, message: dict) -> None:
        self.status = status
        self.message = message
    
    def __str__(self) -> str:
        return(json.dumps({'status': self.status, 'response': self.message}))

class SuccessResponse(Response):
    def __init__(self, message: dict) -> None:
        super().__init__(200, message)

class FailResponse(Response):
    def __init__(self, message: dict) -> None:
        super().__init__(400, message)

class BadRequestResponse(Response):
    def __init__(self, message: dict) -> None:
        super().__init__(300, message)

class UnableToReadException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class InvalidRequestFormatException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class SpreadsheetServer:
    def __init__(self, port: int) -> None:
        self.spreadsheet = None
        self.host = socket.gethostname()
        self.port = port if port > 0 else 5500
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client = None
        self.addr = None
        self.ckpt = './sheet.ckpt'
        self.log = './sheet.log'
        self.loglen = 0
        self.playback()
    
    def playback(self) -> None:
        timestamp = None
        try:
            with open(self.ckpt, 'r') as ckpt:
                data = json.loads(ckpt.read())
                timestamp = date.fromtimestamp(data['timestamp'])
                rows = data['rows']
                cols = data['cols']
                sheet = data['sheet']
                self.spreadsheet = SpreadSheet.Spreadsheet(sheet, rows, cols)
                print('Loaded spreadsheet from checkpoint.')
        except:
            self.spreadsheet = SpreadSheet.Spreadsheet()
        try:
            with open(self.log, 'r') as log:
                for line in log.readlines():
                    req = json.loads(line)
                    time = date.fromtimestamp(req['timestamp'])
                    request = req['request']
                    if timestamp == None or time > timestamp:
                        data = None
                        self.loglen += 1
                        try:
                            data = Request(request['method'], request['args'])
                            self.executeRequest(data, False)
                        except:
                            continue
            print('Replayed changes from log.')
        except:
            return
    
    def bind(self) -> bool:
        try:
            self.socket.bind((self.host, self.port))
            return True
        except:
            return False
    
    def close(self) -> bool:
        if self.client:
            self.client.close()
        self.socket.close()
        return True
    
    def appendLog(self, request: Request) -> None:
        if request.method not in set(['insert', 'remove']):
            return
        with open(self.log, 'a') as log:
            log.write(f'{str(LogEntry(request))}\n')
        self.loglen += 1
        return
    
    def compactLog(self) -> None:
        if self.loglen < 100:
            return
        try:
            self.writeCheckpoint()
            os.remove(self.log)
            self.loglen = 0
        except:
            return
        return
    
    def writeCheckpoint(self) -> None:
        ss = {}
        ss['timestamp'] = time.time()
        ss['rows'] = self.spreadsheet.rows
        ss['cols'] = self.spreadsheet.cols
        ss['sheet'] = self.spreadsheet.data
        with open(f'{self.ckpt}-temp', 'w') as tempckpt:
            tempckpt.write(json.dumps(ss))
        try:
            if os.path.isfile(self.ckpt):
                os.remove(self.ckpt)
            os.rename(f'{self.ckpt}-temp', self.ckpt)
        except:
            os.remove(f'{self.ckpt}-temp')
        return
        
    def run(self):
        print(f'Listening on port {self.port}')
        while True:
            data = None
            while self.client == None:
                self.socket.listen()
                (sock, addr) = self.socket.accept()
                self.client = sock
                self.addr = addr
            
            # try to read an incoming message
            try:
                data = self.read()
            except:
                break
            
            if not data:
                continue

            response = None

            try:
                data = Request(data['method'], data['args'])
            except:
                response = BadRequestResponse({'data': f'{data} is in incorrect format.'})
                self.send(response)
                continue

            response = self.executeRequest(data, True)
            if response:
                self.send(response)

    def read(self) -> dict | None:
        if self.client == None:
            return None
        size = self.client.recv(4)
        if len(size) == 0:
            return None
        size = int.from_bytes(size, byteorder='big')
        response = b""
        while len(response) < size:
            response += self.client.recv(size-len(response))
        response = json.loads(response.decode('utf-8'))
        print(f'{self.addr} > {response}')
        return response

    def send(self, response: Response) -> bool:
        res = str(response).encode('utf-8')
        size = len(res)
        self.client.send(size.to_bytes(4, byteorder='big'))
        self.client.send(res)
        return True
    
    def executeRequest(self, data: Request, respond: bool = True) -> Response | None:
        response = None
        match data.method:
            case 'close':
                if self.client:
                    self.client.close()
                    self.client = None
                    self.addr = None
            case 'insert':
                try:
                    self.spreadsheet.insert(row=data.args['row'], col=data.args['col'], data=data.args['data'])
                    response = SuccessResponse({'data': f'Successful insert at ({data.args["row"]}, {data.args["col"]})'})
                except Exception as e:
                    if e.__class__.__name__ in set(['InvalidCellException']):
                        response = FailResponse(repr(e))
                    else:
                        response = BadRequestResponse(repr(e))
            case 'lookup':
                try:
                    ret = self.spreadsheet.lookup(row=data.args['row'], col=data.args['col'])
                    response = SuccessResponse({'data': ret})
                except Exception as e:
                    if e.__class__.__name__ in set(['InvalidCellException', 'EmptyCellException']):
                        response = FailResponse(repr(e))
                    else:
                        response = BadRequestResponse(repr(e))
            case 'remove':
                try:
                    self.spreadsheet.remove(row=data.args['row'], col=data.args['col'])
                    response = SuccessResponse({'data': f'Successful remove at ({data.args["row"]}, {data.args["col"]})'})
                except Exception as e:
                    if e.__class__.__name__ in set(['InvalidCellException', 'EmptyCellException']):
                        response = FailResponse(repr(e))
                    else:
                        response = BadRequestResponse(repr(e))
            case 'size':
                try:
                    ret = self.spreadsheet.size()
                    response = SuccessResponse({'data': ret})
                except Exception as e:
                    response = BadRequestResponse(repr(e))
            case 'query':
                try:
                    ret = self.spreadsheet.query(row=data.args['row'], col=data.args['col'], width=data.args['width'], height=data.args['height'])
                    response = SuccessResponse({'data': ret})
                except Exception as e:
                    if e.__class__.__name__ in set(['InvalidCellException', 'InvalidDimensionException']):
                        response = FailResponse(repr(e))
                    else:
                        response = BadRequestResponse(repr(e))
            case _:
                response = BadRequestResponse(repr(InvalidRequestFormatException(f'Method {data.method} not supported.')))
        
        if isinstance(response, SuccessResponse):
            self.appendLog(data)
        if self.loglen >= 100:
            self.compactLog()

        if respond:
            return response
        
        return None


def main():
    if len(sys.argv) != 2:
        print("Invalid number of arguments.")
    server = SpreadsheetServer(int(sys.argv[1]))
    if server.bind():
        server.run()

if __name__ == '__main__':
    main()