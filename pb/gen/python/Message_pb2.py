# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Message.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import BaseDefine_pb2 as BaseDefine__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='Message.proto',
  package='Message',
  syntax='proto3',
  serialized_pb=_b('\n\rMessage.proto\x12\x07Message\x1a\x10\x42\x61seDefine.proto\"\xab\x01\n\tIMMsgData\x12\x14\n\x0c\x66rom_user_id\x18\x01 \x01(\r\x12\x15\n\rto_session_id\x18\x02 \x01(\r\x12\x0e\n\x06msg_id\x18\x03 \x01(\r\x12\x13\n\x0b\x63reate_time\x18\x04 \x01(\r\x12%\n\x08msg_type\x18\x05 \x01(\x0e\x32\x13.BaseDefine.MsgType\x12\x10\n\x08msg_data\x18\x06 \x01(\x0c\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"r\n\x0cIMMsgDataAck\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12\x12\n\nsession_id\x18\x02 \x01(\r\x12\x0e\n\x06msg_id\x18\x03 \x01(\r\x12-\n\x0csession_type\x18\x04 \x01(\x0e\x32\x17.BaseDefine.SessionType\"v\n\x10IMMsgDataReadAck\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12\x12\n\nsession_id\x18\x02 \x01(\r\x12\x0e\n\x06msg_id\x18\x03 \x01(\r\x12-\n\x0csession_type\x18\x04 \x01(\x0e\x32\x17.BaseDefine.SessionType\"y\n\x13IMMsgDataReadNotify\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12\x12\n\nsession_id\x18\x02 \x01(\r\x12\x0e\n\x06msg_id\x18\x03 \x01(\r\x12-\n\x0csession_type\x18\x04 \x01(\x0e\x32\x17.BaseDefine.SessionType\"\x11\n\x0fIMClientTimeReq\"&\n\x0fIMClientTimeRsp\x12\x13\n\x0bserver_time\x18\x01 \x01(\r\"9\n\x11IMUnreadMsgCntReq\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"}\n\x11IMUnreadMsgCntRsp\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12\x11\n\ttotal_cnt\x18\x02 \x01(\r\x12/\n\x0funreadinfo_list\x18\x03 \x03(\x0b\x32\x16.BaseDefine.UnreadInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xa1\x01\n\x0fIMGetMsgListReq\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12\x14\n\x0cmsg_id_begin\x18\x04 \x01(\r\x12\x0f\n\x07msg_cnt\x18\x05 \x01(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xb7\x01\n\x0fIMGetMsgListRsp\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12\x14\n\x0cmsg_id_begin\x18\x04 \x01(\r\x12%\n\x08msg_list\x18\x05 \x03(\x0b\x32\x13.BaseDefine.MsgInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"~\n\x13IMGetLatestMsgIdReq\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x95\x01\n\x13IMGetLatestMsgIdRsp\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12\x15\n\rlatest_msg_id\x18\x04 \x01(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\x8f\x01\n\x0fIMGetMsgByIdReq\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12\x13\n\x0bmsg_id_list\x18\x04 \x03(\r\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\"\xa1\x01\n\x0fIMGetMsgByIdRsp\x12\x0f\n\x07user_id\x18\x01 \x01(\r\x12-\n\x0csession_type\x18\x02 \x01(\x0e\x32\x17.BaseDefine.SessionType\x12\x12\n\nsession_id\x18\x03 \x01(\r\x12%\n\x08msg_list\x18\x04 \x03(\x0b\x32\x13.BaseDefine.MsgInfo\x12\x13\n\x0b\x61ttach_data\x18\x14 \x01(\x0c\x42\x19\n\x15\x63om.muduo.im.protobufH\x03\x62\x06proto3')
  ,
  dependencies=[BaseDefine__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_IMMSGDATA = _descriptor.Descriptor(
  name='IMMsgData',
  full_name='Message.IMMsgData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='from_user_id', full_name='Message.IMMsgData.from_user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='to_session_id', full_name='Message.IMMsgData.to_session_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id', full_name='Message.IMMsgData.msg_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='create_time', full_name='Message.IMMsgData.create_time', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_type', full_name='Message.IMMsgData.msg_type', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_data', full_name='Message.IMMsgData.msg_data', index=5,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMMsgData.attach_data', index=6,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=45,
  serialized_end=216,
)


_IMMSGDATAACK = _descriptor.Descriptor(
  name='IMMsgDataAck',
  full_name='Message.IMMsgDataAck',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMMsgDataAck.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMMsgDataAck.session_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id', full_name='Message.IMMsgDataAck.msg_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMMsgDataAck.session_type', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=218,
  serialized_end=332,
)


_IMMSGDATAREADACK = _descriptor.Descriptor(
  name='IMMsgDataReadAck',
  full_name='Message.IMMsgDataReadAck',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMMsgDataReadAck.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMMsgDataReadAck.session_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id', full_name='Message.IMMsgDataReadAck.msg_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMMsgDataReadAck.session_type', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=334,
  serialized_end=452,
)


_IMMSGDATAREADNOTIFY = _descriptor.Descriptor(
  name='IMMsgDataReadNotify',
  full_name='Message.IMMsgDataReadNotify',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMMsgDataReadNotify.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMMsgDataReadNotify.session_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id', full_name='Message.IMMsgDataReadNotify.msg_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMMsgDataReadNotify.session_type', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=454,
  serialized_end=575,
)


_IMCLIENTTIMEREQ = _descriptor.Descriptor(
  name='IMClientTimeReq',
  full_name='Message.IMClientTimeReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=577,
  serialized_end=594,
)


_IMCLIENTTIMERSP = _descriptor.Descriptor(
  name='IMClientTimeRsp',
  full_name='Message.IMClientTimeRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='server_time', full_name='Message.IMClientTimeRsp.server_time', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=596,
  serialized_end=634,
)


_IMUNREADMSGCNTREQ = _descriptor.Descriptor(
  name='IMUnreadMsgCntReq',
  full_name='Message.IMUnreadMsgCntReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMUnreadMsgCntReq.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMUnreadMsgCntReq.attach_data', index=1,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=636,
  serialized_end=693,
)


_IMUNREADMSGCNTRSP = _descriptor.Descriptor(
  name='IMUnreadMsgCntRsp',
  full_name='Message.IMUnreadMsgCntRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMUnreadMsgCntRsp.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='total_cnt', full_name='Message.IMUnreadMsgCntRsp.total_cnt', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='unreadinfo_list', full_name='Message.IMUnreadMsgCntRsp.unreadinfo_list', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMUnreadMsgCntRsp.attach_data', index=3,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=695,
  serialized_end=820,
)


_IMGETMSGLISTREQ = _descriptor.Descriptor(
  name='IMGetMsgListReq',
  full_name='Message.IMGetMsgListReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetMsgListReq.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetMsgListReq.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetMsgListReq.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id_begin', full_name='Message.IMGetMsgListReq.msg_id_begin', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_cnt', full_name='Message.IMGetMsgListReq.msg_cnt', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetMsgListReq.attach_data', index=5,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=823,
  serialized_end=984,
)


_IMGETMSGLISTRSP = _descriptor.Descriptor(
  name='IMGetMsgListRsp',
  full_name='Message.IMGetMsgListRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetMsgListRsp.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetMsgListRsp.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetMsgListRsp.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id_begin', full_name='Message.IMGetMsgListRsp.msg_id_begin', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_list', full_name='Message.IMGetMsgListRsp.msg_list', index=4,
      number=5, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetMsgListRsp.attach_data', index=5,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=987,
  serialized_end=1170,
)


_IMGETLATESTMSGIDREQ = _descriptor.Descriptor(
  name='IMGetLatestMsgIdReq',
  full_name='Message.IMGetLatestMsgIdReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetLatestMsgIdReq.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetLatestMsgIdReq.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetLatestMsgIdReq.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetLatestMsgIdReq.attach_data', index=3,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1172,
  serialized_end=1298,
)


_IMGETLATESTMSGIDRSP = _descriptor.Descriptor(
  name='IMGetLatestMsgIdRsp',
  full_name='Message.IMGetLatestMsgIdRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetLatestMsgIdRsp.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetLatestMsgIdRsp.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetLatestMsgIdRsp.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='latest_msg_id', full_name='Message.IMGetLatestMsgIdRsp.latest_msg_id', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetLatestMsgIdRsp.attach_data', index=4,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1301,
  serialized_end=1450,
)


_IMGETMSGBYIDREQ = _descriptor.Descriptor(
  name='IMGetMsgByIdReq',
  full_name='Message.IMGetMsgByIdReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetMsgByIdReq.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetMsgByIdReq.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetMsgByIdReq.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_id_list', full_name='Message.IMGetMsgByIdReq.msg_id_list', index=3,
      number=4, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetMsgByIdReq.attach_data', index=4,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1453,
  serialized_end=1596,
)


_IMGETMSGBYIDRSP = _descriptor.Descriptor(
  name='IMGetMsgByIdRsp',
  full_name='Message.IMGetMsgByIdRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='Message.IMGetMsgByIdRsp.user_id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_type', full_name='Message.IMGetMsgByIdRsp.session_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='session_id', full_name='Message.IMGetMsgByIdRsp.session_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_list', full_name='Message.IMGetMsgByIdRsp.msg_list', index=3,
      number=4, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_data', full_name='Message.IMGetMsgByIdRsp.attach_data', index=4,
      number=20, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1599,
  serialized_end=1760,
)

_IMMSGDATA.fields_by_name['msg_type'].enum_type = BaseDefine__pb2._MSGTYPE
_IMMSGDATAACK.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMMSGDATAREADACK.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMMSGDATAREADNOTIFY.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMUNREADMSGCNTRSP.fields_by_name['unreadinfo_list'].message_type = BaseDefine__pb2._UNREADINFO
_IMGETMSGLISTREQ.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETMSGLISTRSP.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETMSGLISTRSP.fields_by_name['msg_list'].message_type = BaseDefine__pb2._MSGINFO
_IMGETLATESTMSGIDREQ.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETLATESTMSGIDRSP.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETMSGBYIDREQ.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETMSGBYIDRSP.fields_by_name['session_type'].enum_type = BaseDefine__pb2._SESSIONTYPE
_IMGETMSGBYIDRSP.fields_by_name['msg_list'].message_type = BaseDefine__pb2._MSGINFO
DESCRIPTOR.message_types_by_name['IMMsgData'] = _IMMSGDATA
DESCRIPTOR.message_types_by_name['IMMsgDataAck'] = _IMMSGDATAACK
DESCRIPTOR.message_types_by_name['IMMsgDataReadAck'] = _IMMSGDATAREADACK
DESCRIPTOR.message_types_by_name['IMMsgDataReadNotify'] = _IMMSGDATAREADNOTIFY
DESCRIPTOR.message_types_by_name['IMClientTimeReq'] = _IMCLIENTTIMEREQ
DESCRIPTOR.message_types_by_name['IMClientTimeRsp'] = _IMCLIENTTIMERSP
DESCRIPTOR.message_types_by_name['IMUnreadMsgCntReq'] = _IMUNREADMSGCNTREQ
DESCRIPTOR.message_types_by_name['IMUnreadMsgCntRsp'] = _IMUNREADMSGCNTRSP
DESCRIPTOR.message_types_by_name['IMGetMsgListReq'] = _IMGETMSGLISTREQ
DESCRIPTOR.message_types_by_name['IMGetMsgListRsp'] = _IMGETMSGLISTRSP
DESCRIPTOR.message_types_by_name['IMGetLatestMsgIdReq'] = _IMGETLATESTMSGIDREQ
DESCRIPTOR.message_types_by_name['IMGetLatestMsgIdRsp'] = _IMGETLATESTMSGIDRSP
DESCRIPTOR.message_types_by_name['IMGetMsgByIdReq'] = _IMGETMSGBYIDREQ
DESCRIPTOR.message_types_by_name['IMGetMsgByIdRsp'] = _IMGETMSGBYIDRSP

IMMsgData = _reflection.GeneratedProtocolMessageType('IMMsgData', (_message.Message,), dict(
  DESCRIPTOR = _IMMSGDATA,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMMsgData)
  ))
_sym_db.RegisterMessage(IMMsgData)

IMMsgDataAck = _reflection.GeneratedProtocolMessageType('IMMsgDataAck', (_message.Message,), dict(
  DESCRIPTOR = _IMMSGDATAACK,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMMsgDataAck)
  ))
_sym_db.RegisterMessage(IMMsgDataAck)

IMMsgDataReadAck = _reflection.GeneratedProtocolMessageType('IMMsgDataReadAck', (_message.Message,), dict(
  DESCRIPTOR = _IMMSGDATAREADACK,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMMsgDataReadAck)
  ))
_sym_db.RegisterMessage(IMMsgDataReadAck)

IMMsgDataReadNotify = _reflection.GeneratedProtocolMessageType('IMMsgDataReadNotify', (_message.Message,), dict(
  DESCRIPTOR = _IMMSGDATAREADNOTIFY,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMMsgDataReadNotify)
  ))
_sym_db.RegisterMessage(IMMsgDataReadNotify)

IMClientTimeReq = _reflection.GeneratedProtocolMessageType('IMClientTimeReq', (_message.Message,), dict(
  DESCRIPTOR = _IMCLIENTTIMEREQ,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMClientTimeReq)
  ))
_sym_db.RegisterMessage(IMClientTimeReq)

IMClientTimeRsp = _reflection.GeneratedProtocolMessageType('IMClientTimeRsp', (_message.Message,), dict(
  DESCRIPTOR = _IMCLIENTTIMERSP,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMClientTimeRsp)
  ))
_sym_db.RegisterMessage(IMClientTimeRsp)

IMUnreadMsgCntReq = _reflection.GeneratedProtocolMessageType('IMUnreadMsgCntReq', (_message.Message,), dict(
  DESCRIPTOR = _IMUNREADMSGCNTREQ,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMUnreadMsgCntReq)
  ))
_sym_db.RegisterMessage(IMUnreadMsgCntReq)

IMUnreadMsgCntRsp = _reflection.GeneratedProtocolMessageType('IMUnreadMsgCntRsp', (_message.Message,), dict(
  DESCRIPTOR = _IMUNREADMSGCNTRSP,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMUnreadMsgCntRsp)
  ))
_sym_db.RegisterMessage(IMUnreadMsgCntRsp)

IMGetMsgListReq = _reflection.GeneratedProtocolMessageType('IMGetMsgListReq', (_message.Message,), dict(
  DESCRIPTOR = _IMGETMSGLISTREQ,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetMsgListReq)
  ))
_sym_db.RegisterMessage(IMGetMsgListReq)

IMGetMsgListRsp = _reflection.GeneratedProtocolMessageType('IMGetMsgListRsp', (_message.Message,), dict(
  DESCRIPTOR = _IMGETMSGLISTRSP,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetMsgListRsp)
  ))
_sym_db.RegisterMessage(IMGetMsgListRsp)

IMGetLatestMsgIdReq = _reflection.GeneratedProtocolMessageType('IMGetLatestMsgIdReq', (_message.Message,), dict(
  DESCRIPTOR = _IMGETLATESTMSGIDREQ,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetLatestMsgIdReq)
  ))
_sym_db.RegisterMessage(IMGetLatestMsgIdReq)

IMGetLatestMsgIdRsp = _reflection.GeneratedProtocolMessageType('IMGetLatestMsgIdRsp', (_message.Message,), dict(
  DESCRIPTOR = _IMGETLATESTMSGIDRSP,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetLatestMsgIdRsp)
  ))
_sym_db.RegisterMessage(IMGetLatestMsgIdRsp)

IMGetMsgByIdReq = _reflection.GeneratedProtocolMessageType('IMGetMsgByIdReq', (_message.Message,), dict(
  DESCRIPTOR = _IMGETMSGBYIDREQ,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetMsgByIdReq)
  ))
_sym_db.RegisterMessage(IMGetMsgByIdReq)

IMGetMsgByIdRsp = _reflection.GeneratedProtocolMessageType('IMGetMsgByIdRsp', (_message.Message,), dict(
  DESCRIPTOR = _IMGETMSGBYIDRSP,
  __module__ = 'Message_pb2'
  # @@protoc_insertion_point(class_scope:Message.IMGetMsgByIdRsp)
  ))
_sym_db.RegisterMessage(IMGetMsgByIdRsp)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\025com.muduo.im.protobufH\003'))
# @@protoc_insertion_point(module_scope)
