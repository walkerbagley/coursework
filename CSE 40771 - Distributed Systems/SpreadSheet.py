
class InvalidCellException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class EmptyCellException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class InvalidDimensionException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class Spreadsheet:
    # def __init__(self) -> None:
    #     self.data = {}
    #     self.rows = 0
    #     self.cols = 0
    
    def __init__(self, data: dict = {}, rows: int = 0, cols: int = 0) -> None:
        self.data = data
        self.rows = rows
        self.cols = cols
    
    def insert(self, row: int, col: int, data: dict) -> bool:
        if row < 1 or col < 1:
            raise InvalidCellException(f'({row}, {col}) is not a valid cell.')
        if row not in self.data:
            self.data[row] = {}
        self.data[row][col] = data
        self.rows = max(self.rows, row)
        self.cols = max(self.cols, col)
        return True
    
    def lookup(self, row: int, col: int) -> dict:
        if row < 1 or col < 1:
            raise InvalidCellException(f'({row}, {col}) is not a valid cell.')
        if row not in self.data or col not in self.data[row]:
            raise EmptyCellException(f'No data found at ({row}, {col})')
        return self.data[row][col]

    def remove(self, row: int, col: int) -> bool:
        if row < 1 or col < 1:
            raise InvalidCellException(f'({row}, {col}) is not a valid cell.')
        if row not in self.data or col not in self.data[row]:
            raise EmptyCellException(f'No data to delete at ({row}, {col})')
        del self.data[row][col]
        if len(self.data[row]) == 0:
            del self.data[row]
        update = [row == self.rows, col == self.cols]
        if update[0] or update[1]:
            self.rows = 0 if update[0] else self.rows
            self.cols = 0 if update[1] else self.cols
            for r in self.data:
                if update[0]:
                    self.rows = max(self.rows, r)
                for c in self.data[r]:
                    if update[1]:
                        self.cols = max(self.cols, c)
        return True
    
    def size(self) -> dict:
        return {'rows': self.rows, 'cols': self.cols}
    
    def query(self, row: int, col: int, width: int, height: int) -> dict:
        if row < 1 or col < 1:
            raise InvalidCellException(f'({row}, {col}) is not a valid starting cell.')
        if width < 1 or height < 1:
            raise InvalidDimensionException(f'({width}, {height}) is not a valid rectangle.')
        q = {}
        for r, roww in self.data.items():
            for c, cell in roww.items():
                if row <= r <= row + width - 1 and col <= c <= col + height - 1:
                    if r not in q:
                        q[r] = {}
                    q[r][c] = cell
        return q