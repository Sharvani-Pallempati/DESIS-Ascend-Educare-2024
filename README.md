# Multi User Chat System

## Overview
The Multi User Chat System is a client-server application implemented in C++ using Windows Sockets (WinSock). It supports real-time communication between multiple clients, allowing them to send and receive messages via a central server. The application demonstrates the use of socket programming, multithreading, and file logging.

## Features
- **Multi-client Communication:** Multiple clients can connect to the server and exchange messages.
- **Direct Messaging:** Clients can send private messages to specific users by following a predefined message format.
- **Chat Logging:** All messages are logged in `chat_history.txt` for server-side record keeping.
- **Concurrent Handling:** The server uses multithreading to handle multiple clients simultaneously without blocking.

## File Structure
- **Client Code:** Implements the client-side application to send and receive messages.
- **Server Code:** Manages connections and relays messages between clients.

## Setup and Usage

### Step 1: Compile the Server and Client Code
1. Open the server and client code files in your C++ IDE or text editor.
2. Compile both files separately. Ensure the WinSock library (`ws2_32.lib`) is linked during compilation.

### Step 2: Start the Server
1. Run the compiled server executable.
2. The server will start listening on port `12345` for incoming connections.

### Step 3: Connect Clients
1. Run the compiled client executable on the same or different machines.
2. Each client will be prompted to enter a unique chat name upon connecting.

### Step 4: Exchange Messages
- Clients can send messages using the following formats:
  - **Broadcast Message:** Any message typed will be logged and sent to all connected clients.
  - **Direct Message:** Use the format `To recipient_name message` to send a private message to a specific client.
- To disconnect, type `Exit`.

### Step 5: Review Chat Logs
- The server logs all messages in `chat_history.txt` for review.

## Example Usage
1. **Server Output:**
- Server started listening on port 12345 Alice connected... Bob connected...

2. **Client Interaction:**
- Alice: `To Bob Hello, Bob!`
- Bob: `Thanks, Alice!`
