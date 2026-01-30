FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ cmake python3 python3-pip git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY src/engine/ ./src/engine/
COPY src/backend/ ./src/backend/
COPY CMakeLists.txt .

RUN mkdir build && cd build && cmake .. && make

WORKDIR /app/src/backend
RUN pip3 install fastapi uvicorn

EXPOSE 8000
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]
