#!/usr/bin/env python3
import os
import sys

def read_raw_data(path) -> list:
    """read raw html data

    Args:
        path (str): the path of html file

    Returns:
        str: return the content of html file
    """
    content = []
    with open(path, "r") as fp:
        content = fp.readlines()
    fp.close()
    return content

def main() -> None:
    output_name = "index.h"
    content_list = read_raw_data(sys.argv[1]);
    if len(sys.argv) == 3:
        output_name = sys.argv[2]
    
    # print(content_list, output_name)
    
    pass

def usage() -> None:
    print("""Usage: python3 ./{} <html> [output]
          """.format(sys.argv[0]))
    pass

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
        exit()
    else:
        print(sys.argv)
    main()
    