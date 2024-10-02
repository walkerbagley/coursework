
import argparse
import time

import SpreadSheetClient

SIZE = 31


def main(args: argparse.Namespace):
    server = args.server
    port = args.port

    spreadsheet = SpreadSheetClient.SpreadsheetClient(server, port)
    data = {"walker": 'A'}

    # Test performance of insert.
    best_insert = float('inf')
    worst_insert = 0
    best_remove = float('inf')
    worst_remove = 0
    for i in range(1, SIZE + 1):
        for j in range(1, SIZE + 1):
            start = time.time_ns()
            spreadsheet.insert(i, j, data)
            end = time.time_ns()
            best_insert = min(best_insert, end - start)
            worst_insert = max(worst_insert, end - start)

            start = time.time_ns()
            spreadsheet.remove(i, j)
            end = time.time_ns()
            best_remove = min(best_remove, end - start)
            worst_remove = max(worst_remove, end - start)

    n_operations = SIZE * SIZE
    print(f"Insert ({n_operations})")
    print(f"- Best (ms):  {best_insert / 1000000}")
    print(f"- Worst (ms): {worst_insert / 1000000}")

    print(f"Remove ({n_operations})")
    print(f"- Best (ms):  {best_remove / 1000000}")
    print(f"- Worst (ms): {worst_remove / 1000000}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("server", type=str)
    parser.add_argument("port", type=int)
    args = parser.parse_args()
    main(args)
