from fastapi import FastAPI, File, UploadFile
import subprocess
import shutil
import os
import json

app = FastAPI()

UPLOAD_DIR = "uploads"
os.makedirs(UPLOAD_DIR, exist_ok=True)

@app.post("/compute-max-flow/")
async def compute_max_flow(file: UploadFile = File(...)):
    file_location = os.path.join(UPLOAD_DIR, file.filename)
    with open(file_location, "wb") as f:
        shutil.copyfileobj(file.file, f)

    # Call C++ compiled engine (assumes executable named network_flow)
    output_file = os.path.join(UPLOAD_DIR, "result.json")
    subprocess.run(["./network_flow", file_location, output_file])

    with open(output_file) as f:
        result = json.load(f)

    return result
