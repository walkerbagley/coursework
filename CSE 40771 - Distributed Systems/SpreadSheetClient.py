import socket
import sys
import json
from SpreadSheetServer import Request

class CloseRequest(Request):
    def __init__(self) -> None:
        super().__init__('close', {})

class InvalidOperationException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class InvalidConnectionException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class SpreadsheetClient:
    def __init__(self, host: str, port: int) -> None:
        self.host = host
        self.port = port if port > 0 else 5500
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connect()

    def connect(self) -> bool:
        try:
            self.socket.connect((self.host, self.port))
            return True
        except:
            raise InvalidConnectionException(f'Unable to connect to ({self.host}, {self.port})')
    
    # def run(self):
    #     while True:
    #         mesg = input('>>> ')
    #         mesg = self.parseMessage(mesg)
    #         self.send()
    #         response = self.
    #         if mesg.lower() == 'closed':
    #             break
            # self.insert(1, 1, 1)

    # def write(self, mesg: str) -> bool:
    #     mesg, success = self.parseMessage(mesg)
    #     if not success:
    #         print(mesg)
    #         return False
    #     self.socket.send(mesg.encode('utf-8'))

    # def parseMessage(self, mesg: str) -> tuple[(str, bool)]:
    #     method, *tokens = [i.lower() for i in mesg.split()]
    #     print(method, tokens)
    #     operations = {'insert': 3, 'lookup': 2, 'remove': 2, 'size': 0, 'query': 4}
    #     if method not in operations:
    #         return (f'{method} is not a valid operation', False)
    #         # raise InvalidOperationException(f'{method} is not a valid operation')
    #     if len(tokens) > operations[method]:
    #         return (f'Too many arguments: {len(tokens)} > {operations[method]}', False)
    #     if len(tokens) < operations[method]:
    #         return (f'Too few arguments: {len(tokens)} < {operations[method]}', False)
    #     return ('Successful operation', True)

    def close(self) -> bool:
        self.send(CloseRequest())
        self.socket.close()
        return True
        # raise InvalidConnectionException('Unable to close client socket.')

    def insert(self, row: int, col: int, data: dict) -> dict:
        request = Request('insert', {'row': row, 'col': col, 'data': data})
        self.send(request)
        return self.getResponse()
    
    def lookup(self, row: int, col: int) -> dict:
        request = Request('lookup', {'row': row, 'col': col})
        self.send(request)
        return self.getResponse()

    def remove(self, row: int, col: int) -> dict:
        request = Request('remove', {'row': row, 'col': col})
        self.send(request)
        return self.getResponse()
    
    def size(self) -> dict:
        request = Request('size', {})
        self.send(request)
        return self.getResponse()
    
    def query(self, row: int, col: int, width: int, height: int) -> dict:
        request = Request('query', {'row': row, 'col': col, 'width': width, 'height': height})
        self.send(request)
        return self.getResponse()
    
    def send(self, request: Request) -> None:
        req = str(request).encode('utf-8')
        size = len(req)
        self.socket.send(size.to_bytes(4, byteorder='big'))
        self.socket.send(req)
        return True

    def getResponse(self) -> dict:
        size = self.socket.recv(4)
        if len(size) == 0:
            return None
        size = int.from_bytes(size, byteorder='big')
        response = b""
        while len(response) < size:
            response += self.socket.recv(size - len(response))
        response = json.loads(response.decode('utf-8'))
        return response

def main():
    # if len(sys.argv) != 3:
    #     print("Invalid number of arguments.")
    # client = SpreadsheetClient(sys.argv[1], int(sys.argv[2]))
    # client.connect()
    # client.run()
    pass

if __name__ == '__main__':
    main()