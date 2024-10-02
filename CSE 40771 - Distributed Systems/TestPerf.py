
import argparse
import time

import SpreadSheetClient

SIZE = 50


def main(args: argparse.Namespace):
    server = args.server
    port = args.port

    # spreadsheet = SpreadSheet.SpreadSheet()
    spreadsheet = SpreadSheetClient.SpreadsheetClient(server, port)
    data = {"walker": 'A'}

    # Test performance of insert.
    start = time.time()
    for i in range(1, SIZE + 1):
        for j in range(1, SIZE + 1):
            spreadsheet.insert(i, j, data)
    end = time.time()
    insert_time = end - start

    # Test performance of lookup.
    start = time.time()
    for i in range(1, SIZE + 1):
        for j in range(1, SIZE + 1):
            spreadsheet.lookup(i, j)
    end = time.time()
    lookup_time = end - start

    # Test performance of size.
    start = time.time()
    for i in range(1, SIZE + 1):
        for j in range(1, SIZE + 1):
            spreadsheet.size()
    end = time.time()
    size_time = end - start

    # Test performance of query.
    start = time.time()
    spreadsheet.query(1, 1, SIZE, SIZE)
    end = time.time()
    query_time = end - start

    # Test performance of remove.
    start = time.time()
    for i in range(1, SIZE + 1):
        for j in range(1, SIZE + 1):
            spreadsheet.remove(i, j)
    end = time.time()
    remove_time = end - start

    n_operations = SIZE * SIZE
    print(f"Insert ({n_operations})")
    print(f"- Time (s):           {insert_time}")
    print(f"- Throughput (ops/s): {n_operations / insert_time}")
    print(f"- Latency (s):        {insert_time / n_operations}")

    print(f"Lookup ({n_operations})")
    print(f"- Time (s):           {lookup_time}")
    print(f"- Throughput (ops/s): {n_operations / lookup_time}")
    print(f"- Latency (s):        {lookup_time / n_operations}")

    print(f"Size ({n_operations})")
    print(f"- Time (s):           {size_time}")
    print(f"- Throughput (ops/s): {n_operations / size_time}")
    print(f"- Latency (s):        {size_time / n_operations}")

    print(f"Query ({n_operations})")
    print(f"- Time (s):           {query_time}")

    print(f"Remove ({n_operations})")
    print(f"- Time (s):           {remove_time}")
    print(f"- Throughput (ops/s): {n_operations / remove_time}")
    print(f"- Latency (s):        {remove_time / n_operations}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("server", type=str)
    parser.add_argument("port", type=int)
    args = parser.parse_args()
    main(args)
