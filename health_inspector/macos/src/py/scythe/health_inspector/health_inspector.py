import uuid
import json
import health_inspector

g_client = None

CATEGORY_WORKER = 4
HEALTH_INSPECTOR_MODULE_ID = uuid.UUID('4e5f74d0-4705-11ec-abd0-e12370ec4fc6')

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
    #message_dict = json.loads(message.decode('utf-8'))

    result = health_inspector.main()
    result = "\n".join(result)
    result = ''.join([c for c in result if ord(c) > 31 or ord(c) == 9])

    # Turn into bytes
    message = result.encode('utf-8')
    
    #return message
    return message


def getinfo():
    """

    :return:
    """
    return { "type": CATEGORY_WORKER, "version" : {"major": 2, "minor": 0}, "id" : HEALTH_INSPECTOR_MODULE_ID}


def deinit(**kwargs):
    """

    :param kwargs:
    :return:
    """
    return True
