import sys, os

def test_mysql():
    try:
        import MySQLdb
    except Exception as e:
        print >> sys.stdout, str(e)

if __name__ == "__main__":
    test_mysql()
