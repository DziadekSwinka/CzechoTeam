import socket as soc
import time
import json

port=1313
ip="172.16.0.186"
is_running=True

server_socet=soc.socket(soc.AF_INET,soc.SOCK_DGRAM)
while is_running:
    h=0
    t=0
    data={"temp":str(t),"hum":str(h)}
    json_data=json.dumps(data)
    server_socet.sendto(json_data.encode(),(ip,port))
    time.sleep(1)
server_socet.close()
input()
