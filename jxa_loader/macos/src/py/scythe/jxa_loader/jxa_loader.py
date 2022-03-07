import uuid
import json
import jxa_loader

g_client = None

CATEGORY_WORKER = 4
JXA_LOADER_MODULE_ID = uuid.UUID('03107e60-398c-11ec-ba0e-5d31a0f9523e')

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
    message_dict = json.loads(message.decode("utf-8"))
    # Get result of main's return
    
    result = jxa_loader.main(filename=message_dict['filename'],vfs=message_dict['vfs'])
    result = "\n".join(result)
    #result = ''.join([c for c in result if ord(c) > 31 or ord(c) == 9])
    
    # Turn into bytes
    message = result.encode("utf-8")

    return message


def getinfo():
    """

    :return:
    """
    return { "type": CATEGORY_WORKER, "version" : {"major": 1, "minor": 0.1}, "id" : JXA_LOADER_MODULE_ID}


def deinit(**kwargs):
    """

    :param kwargs:
    :return:
    """
    return True
