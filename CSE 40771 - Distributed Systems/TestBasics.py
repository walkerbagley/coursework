import unittest
import socket
import sys
import SpreadSheet
import SpreadSheetServer
import SpreadSheetClient

class SpreadSheetBasicsTest(unittest.TestCase):
    def setUp(self) -> None:
        self.ss = SpreadSheet.Spreadsheet()
    
    def testValidInsert(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertTrue(self.ss.insert(1, 1, {'message': 'Hello World!'}))
        self.assertDictEqual(self.ss.size(), {'rows': 1, 'cols': 1})
    
    def testInvalidInsert(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.InvalidCellException, self.ss.insert, -1, -1, {'message': 'Hello World!'})
    
    def testValidLookup(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertTrue(self.ss.insert(1, 1, {'message': 'Hello World!'}))
        self.assertDictEqual(self.ss.size(), {'rows': 1, 'cols': 1})
        self.assertEqual(self.ss.lookup(1, 1)['message'], 'Hello World!')
    
    def testInvalidCellLookup(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.InvalidCellException, self.ss.lookup, -1, -1)
    
    def testEmptyCellLookup(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.EmptyCellException, self.ss.lookup, 1, 1)
    
    def testValidRemove(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertTrue(self.ss.insert(1, 1, {'message': 'Hello World!'}))
        self.assertDictEqual(self.ss.size(), {'rows': 1, 'cols': 1})
        self.assertTrue(self.ss.remove(1, 1))
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
    
    def testInvalidCellRemove(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.InvalidCellException, self.ss.remove, -1, -1)
    
    def testEmptyCellRemove(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.EmptyCellException, self.ss.remove, 1, 1)

    def testValidQuery(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertTrue(self.ss.insert(1, 1, {'message': 'Hello World!'}))
        self.assertDictEqual(self.ss.size(), {'rows': 1, 'cols': 1})
        self.assertDictEqual(self.ss.query(1, 1, 1, 1), {1: {1: {'message': 'Hello World!'}}})
    
    def testInvalidQueryStart(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.InvalidCellException, self.ss.query, -1, -1, 1, 1)
    
    def testInvalidQuerySize(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        self.assertRaises(SpreadSheet.InvalidDimensionException, self.ss.query, 1, 1, -1, -1)
    
    def testEverything(self):
        self.assertDictEqual(self.ss.size(), {'rows': 0, 'cols': 0})
        for i in range(1, 21):
            self.assertTrue(self.ss.insert(i, i, i))
            self.assertEqual(self.ss.lookup(i, i), i)
            self.assertDictEqual(self.ss.size(), {'rows': i, 'cols': i})
        self.assertTrue(self.ss.insert(10, 10, 100))
        self.assertEqual(self.ss.lookup(10, 10), 100)
        self.assertEqual(len(self.ss.query(1, 1, 20, 20)), 20)
        self.assertEqual(len(self.ss.query(1, 1, 20, 1)), 1)
        self.assertTrue(self.ss.remove(20, 20))
        self.assertDictEqual(self.ss.size(), {'rows': 19, 'cols': 19})
        for i in range(1, 20):
            self.assertTrue(self.ss.remove(i, i))
        self.assertRaises(SpreadSheet.EmptyCellException, self.ss.remove, 20, 20)

class SpreadSheetServerTest(unittest.TestCase):
    def setUp(self) -> None:
        self.server = SpreadSheetServer.SpreadsheetServer(9999)

    def testServerSetup(self):
        self.assertTrue(self.server.bind())
        self.assertTrue(self.server.close())

class SpreadSheetClientTest(unittest.TestCase):
    host = None
    port = None

    def setUp(self) -> None:
        self.client = SpreadSheetClient.SpreadsheetClient(self.host, self.port)
    
    def tearDown(self) -> None:
        self.client.close()
    
    def testInsertValid(self):
        self.client.insert(1, 1, 1)
        self.assertEqual(self.client.lookup(1, 1)['response']['data'], 1)
        self.client.remove(1, 1)

        self.client.insert(1, 1, 2)
        self.assertEqual(self.client.lookup(1, 1)['response']['data'], 2)
        self.client.remove(1, 1)

        self.client.insert(1, 1, {"complex": {"data": 3}})
        self.assertEqual(self.client.lookup(1, 1)['response']['data'],
                         {"complex": {
                             "data": 3
                         }})
        self.client.remove(1, 1)

        self.client.insert(53, 91, "walker")
        self.client.insert(53, 91, "walker")
        self.assertEqual(self.client.lookup(53, 91)['response']['data'], "walker")
        self.client.remove(53, 91)

    def testLookupValid(self):
        self.client.insert(1, 1, 1)
        self.assertEqual(self.client.lookup(1, 1)['response']['data'], 1)
        self.assertEqual(self.client.lookup(1, 1),
                         self.client.lookup(1, 1))
        self.client.remove(1, 1)

        self.client.insert(999, 999, {})
        self.assertEqual(self.client.lookup(999, 999)['response']['data'], {})
        self.client.remove(999, 999)

    def testRemoveValid(self):
        self.client.insert(1, 1, 1)
        self.assertEqual(self.client.lookup(1, 1)['response']['data'], 1)
        self.client.remove(1, 1)
        self.assertIn('EmptyCellException', self.client.lookup(1, 1)['response'])

        self.client.insert(3131, 1313, [92, 5, 3])
        self.assertEqual(self.client.lookup(3131, 1313)['response']['data'], [92, 5, 3])
        self.client.remove(3131, 1313)
        self.client.remove(3131, 1313)
        self.assertIn('EmptyCellException', self.client.lookup(3131, 1313)['response'])

        self.client.remove(123456789, 987654321)

    def testQueryValid(self):
        self.client.insert(1, 1, 1)
        self.assertEqual(self.client.query(1, 1, 1, 1)['response']['data'], {'1': {'1': 1}})
        self.client.remove(1, 1)

        self.client.insert(5, 5, "string")
        self.assertEqual(self.client.query(5, 4, 1, 2)['response']['data'],
                         {'5': {'5': "string"}})
        self.client.remove(5, 5)

        self.client.insert(8, 7, {"nice": 1})
        self.client.insert(7, 8, {"man": 2})
        self.assertEqual(self.client.query(3, 3, 6, 5)['response']['data'],
                         {'8': {'7': {
                              "nice": 1
                          }}})
        self.assertEqual(self.client.query(3, 3, 5, 6)['response']['data'],
                         {'7': {'8': {
                              "man": 2
                          }}})
        self.assertEqual(self.client.query(3, 3, 6, 6)['response']['data'], 
                         {'8': {'7': {
                              "nice": 1
                          }},
                          '7': {'8': {
                              "man": 2
                          }}
                        })
        self.client.remove(8, 7)
        self.client.remove(7, 8)

    def testSizeValid(self):
        self.client.insert(1, 1, 1)
        self.assertEqual(self.client.size()['response']['data'], {'rows': 1, 'cols': 1})
        self.client.remove(1, 1)

        self.client.insert(1, 5, 1)
        self.assertEqual(self.client.size()['response']['data'], {'rows': 1, 'cols': 5})
        self.client.insert(5, 1, 1)
        self.assertEqual(self.client.size()['response']['data'], {'rows': 5, 'cols': 5})
        self.client.remove(1, 5)
        self.assertEqual(self.client.size()['response']['data'], {'rows': 5, 'cols': 1})
        self.client.remove(5, 1)
        self.assertEqual(self.client.size()['response']['data'], {'rows': 0, 'cols': 0})

    def testInsertInvalid(self):
        self.assertIn('InvalidCellException', self.client.insert(0, 5, 1)['response'])
        self.assertIn('InvalidCellException', self.client.insert(-1, 5, 1)['response'])
        self.assertIn('InvalidCellException', self.client.insert(5, 0, 1)['response'])
        self.assertIn('InvalidCellException', self.client.insert(-1, 5, 1)['response'])

    def testLookupInvalid(self):
        self.assertIn('InvalidCellException', self.client.lookup(0, 0)['response'])
        self.assertIn('InvalidCellException', self.client.lookup(-1, 1)['response'])
        self.assertIn('InvalidCellException', self.client.lookup(1, -1)['response'])
        self.assertIn('EmptyCellException', self.client.lookup(1, 1)['response'])

        self.client.insert(5, 3, 1)
        self.assertIn('EmptyCellException', self.client.lookup(3, 5)['response'])
        self.client.remove(5, 3)

    def testRemoveInvalid(self):
        self.assertIn('InvalidCellException', self.client.remove(0, 0)['response'])
        self.assertIn('InvalidCellException', self.client.remove(-1, 1)['response'])
        self.assertIn('InvalidCellException', self.client.remove(1, -1)['response'])
        self.assertIn('EmptyCellException', self.client.remove(1, 1)['response'])

    def testQueryInvalid(self):
        self.assertIn('InvalidCellException', self.client.query(0, 0, 1, 1)['response'])
        self.assertIn('InvalidDimensionException', self.client.query(1, 1, 1, -1)['response'])
        self.assertIn('InvalidDimensionException', self.client.query(1, 1, -1, 1)['response'])

def main():
    if len(sys.argv) != 3:
        raise Exception("Invalid number of arguments.")
    try:
        port = int(sys.argv.pop())
        host = sys.argv.pop()
        SpreadSheetClientTest.port = port
        SpreadSheetClientTest.host = host
    except:
        raise Exception('Invalid arguments.')
    
    unittest.main()

if __name__ == '__main__':
    main()