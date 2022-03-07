import uuid
import orchard
import json

g_client = None

CATEGORY_WORKER = 4
ORCHARD_MODULE_ID = uuid.UUID('8baea9b0-47c2-11ec-91ab-af76d7f49ebf')

def init(client, **kwargs):
    """

    :param client:
    :param kwargs:
    :return:
    """
    global g_client
    g_client = client
    return True


def run(message,  **kwargs):
    """

    :param bytes message:
    :param kwargs:
    :return bytes or None: None if post will happen asynchronously
    """
    result = orchard.main()
    result = "\n".join(result)
    
    result = ''.join([c for c in result if ord(c) > 31 or ord(c) == 9])
    # Turn into bytes
    message = result.encode('utf-8')
    
    return message


def getinfo():
    """

    :return:
    """
    return { "type": CATEGORY_WORKER, "version" : {"major": 1, "minor": 0}, "id" : ORCHARD_MODULE_ID}


def deinit(**kwargs):
    """

    :param kwargs:
    :return:
    """
    return True
