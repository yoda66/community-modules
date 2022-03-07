# Copyright (c) SCYTHE, Inc. Use is subject to agreement.

import argparse
import ast
import json
import shlex
import struct
from argparse import Namespace


# noinspection PyUnusedLocal
def create_parser(db, os="windows"):
    class ArgumentParser(argparse.ArgumentParser):
        def error(self, message):
            raise ValueError(message)

    epilog =  'Example usage: scythe.lmo --ports [80,443,53] --domain testdomain.com'
    parser = ArgumentParser(prog="scythe.lmo", description="This is a checker to see if a host can talk outbound to LetMeOutOfYour.net",
                            epilog=epilog)
    parser.add_argument(
        "--ports", help="Ports to try and beacon out to. Default: [80,443,445,8080,3389,22,21]",
        required=False, default="[80,443,445,8080,3389,22,21]"
    )
    parser.add_argument(
        "--domain", help='Domain to try and beacon out to. Default: letmeoutofyour.net',
        required=False, default="letmeoutofyour.net"
    )

    return parser


def usage(db, os):
    """Return the usage of this module as a string
    :return str: Usage string for this module
    """
    return create_parser(db, os).format_help()

# noinspection PyUnusedLocal
def tags(reserved, request, response):
        return ["scythe", "att&ck", "att&ck-technique:T1016","att&ck-technique:T1016.001"]

# noinspection PyUnusedLocal
def succeeded(reserved, request,response):
    result = False
    if response and len(response) > 72:
        content = response[72:].tobytes().decode("utf-8")
        if not "Error:" in content:
            result = True
    return result


# noinspection PyUnusedLocal
def create_message_body(db, command_line, campaign_name, endpoint_name):
    """Create a SCYTHE message body
    :param db: used only to retrieve operating system
    :param str command_line: command line string. If None is provided, command line will be received from sys.argv
    :param campaign_name: ignored
    :param endpoint_name: ignored
    :return bytes: message body bytes
    """
    # You may call: db.get_setting_value("language")
    # This will return a language id string such as: "en-US"
    # You may use this result to present localized strings in the user interface.

    # You may call: db.get_campaign_operating_system_name(campaign_name)
    # This will return "windows" for Windows campaigns.
    parser = create_parser(db, db.get_campaign_operating_system_name(campaign_name))

    # Get arguments/defaults
    argv = shlex.split(command_line, posix=False)
    args = parser.parse_args(argv)

    # Convert Array String to Array
    try:
        ports = ast.literal_eval(args.ports)
    except:
        raise ValueError("Error: --ports could not be parsed with value: '%s'!" % args.ports)

    dict_to_send = {
        "ports": ports,
        "domain": args.domain
	}

    return json.dumps(dict_to_send).encode("utf-8")


# noinspection PyUnusedLocal
def report(db, request, response, format_):
    """Generate a report for a request and response for this module
    :param db: ignored
    :param request: Request to report on
    :param response: Response to report on
    :param format_: ignored, always pre
    :return tuple(str, str, str): request report, response report, and format
    """
    # size of the response message is response[64:72]
    sz = struct.unpack("<Q", request[64:72].tobytes())[0]
    request_contents = request[72:72 + sz].tobytes().decode("utf-8")

    # format request_contents
    request_contents = json.loads(request_contents)
    request_formatted = "--ports %s --domain %s" % (
        request_contents['ports'],
        request_contents['domain']
	)

    content = response[72:].tobytes().decode("utf-8")
    return "%s" % request_formatted, content, "pre"


def main():
    pass


if __name__ == "__main__":
    main()
