import uuid
import json
import lmo_oob
g_client = None

CATEGORY_WORKER = 4
TEST_LMO_MODULE_ID = uuid.UUID('c97a9e30-3961-11ec-80c2-7778778f744a')

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
    # Load dict from message
    message_dict = json.loads(message.decode("utf-8"))
    # Get result of main's return
    result = lmo_oob.main(
        ports=message_dict["ports"],
        domain=message_dict["domain"]
    )
    # Turn result into string
    result = "\n".join(result)
    result = ''.join([c for c in result if ord(c) > 31 or ord(c) == 9])
    # Turn into bytes
    message = result.encode('utf-8')

    return message

def getinfo():
    """

    :return:
    """
    return { "type": CATEGORY_WORKER, "version" : {"major": 1, "minor": 0}, "id" : TEST_LMO_MODULE_ID}


def deinit(**kwargs):
    """

    :param kwargs:
    :return:
    """
    return True
