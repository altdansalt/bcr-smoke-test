"""py_proto_library smoke: build a message, round-trip it through serialization."""

import unittest

from python import person_pb2


class PersonProtoTest(unittest.TestCase):
    def test_roundtrip(self):
        p = person_pb2.Person(name="Ada", id=7, emails=["ada@example.com"])
        data = p.SerializeToString()
        q = person_pb2.Person.FromString(data)
        self.assertEqual(q, p)
        self.assertEqual(q.name, "Ada")
        self.assertEqual(list(q.emails), ["ada@example.com"])


if __name__ == "__main__":
    unittest.main()
