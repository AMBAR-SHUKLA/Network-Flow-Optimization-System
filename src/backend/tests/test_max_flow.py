import requests

url = "http://127.0.0.1:8000/compute-max-flow/"

with open("../data/sample_graph.txt", "rb") as f:
    r = requests.post(url, files={"file": f})

print(r.json())
