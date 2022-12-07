#!/usr/bin/env python3
import os
import sys

OUTPUT_PATH = "./index.h"

def read_raw_data(path) -> list:
    """read raw html data

    Args:
        path (str): the path of html file

    Returns:
        str: return the content of html file
    """
    print(f"reading raw data from {sys.argv[1]}")
    list_content = []
    with open(path, "r") as fp:
        list_content = fp.readlines()
    fp.close()
    return list_content

def generate_c_header_file(list_web_content, output):
    # print(list_web_content, output)
    with open(output, "w") as fp:
        fp.write("#ifndef __INDEX_H\n")
        fp.write("#define __INDEX_H\n")

        fp.write("""#define INDEX_HTML_CONTENT \"""")
        for line in list_web_content:
            pure_line  = line.split("\n")[0]
            # should give each `"` a `\`
            pure_line = pure_line.replace("\"", "\\\"")
            fp.write(pure_line+"\\\n");
        fp.write("\"")

        fp.write("\n#endif\n")
    fp.close()
    print(f"file has been generated at {output}")

def main() -> None:
    output_path = OUTPUT_PATH
    list_web_content = read_raw_data(sys.argv[1]);
    if len(sys.argv) == 3:
        output_path = sys.argv[2]

    generate_c_header_file(list_web_content, output_path)

def usage() -> None:
    print("""Usage: python3 {} <html_file> [output_name]
          """.format(sys.argv[0]))
    pass

if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()
        exit()
    else:
        # print(sys.argv)
        pass
    main()
