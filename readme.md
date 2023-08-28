# node-nexusdb

This module provides a node interface to the NexusDB database engine.

## Installation

```bash
npm install node-nexusdb
```

## Usage

```javascript
const nexusdb = require("node-nexusdb");

nexusdb.loadDll();

const db_local = nexusdb.NexusLocalDatabase("test-db")
db_local.execute("CREATE TABLE users (id INTEGER, name VARCHAR(255))")
db_local.execute("INSERT INTO users (id, name) VALUES (1, 'Franz')")
const res2 = db_local.execute("SELECT * FROM users")
console.log(res2);
db_local.close();

const db_remote = nexusdb.NexusRemoteDatabase("127.0.0.1", "test-db", "administrator", "NexusDB")
const res = db_remote.execute("SELECT * FROM test_table")
console.log(res);
db_remote.close();

nexusdb.unloadDll();
```

## Requirements

* Node.js 8.0 or higher
* Windows 7 or higher

### Build Requirements

* NexusDB 4.50 or higher
* Node.js 8.0 or higher
* Windows 7 or higher
* Delphi 12 or higher

## Build

```bash
make
```
