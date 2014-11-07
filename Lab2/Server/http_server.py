from http.server import *

server_address = ('192.168.1.1', 60000)
httpd = HTTPServer(server_address, BaseHTTPRequestHandler)
httpd.serve_forever()
