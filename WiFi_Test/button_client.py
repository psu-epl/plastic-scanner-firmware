import websocket

def on_message(ws, message):
    print(message)

def on_open(ws):
    print("Connected to Arduino.")

def on_error(ws, error):
    print(error)

def on_close(ws, close_status_code, close_msg):
    print("Connection closed.")

if __name__ == "__main__":
    ws = websocket.WebSocketApp(
        "ws://172.20.10.7:81/",  # Your Arduino's IP
        on_open=on_open,
        on_message=on_message,
        on_error=on_error,
        on_close=on_close
    )
    ws.run_forever()