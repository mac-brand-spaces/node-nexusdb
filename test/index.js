const nexusdb = require("./../src/nexusdb");

nexusdb.loadDll(__dirname + "/../nexusdb-lib/Win64/Debug/Project1.dll");

const db_local = nexusdb.NexusLocalDatabase("C:\\Users\\KEHL\\Desktop\\c")
// db_local.execute("CREATE TABLE users (id INTEGER, name VARCHAR(255))")
db_local.execute("INSERT INTO users (id, name) VALUES (1, 'Kehl')")
const res2 = db_local.execute("SELECT * FROM users")
console.log(res2);
db_local.close();

const db_remote = nexusdb.NexusRemoteDatabase("127.0.0.1", "Docuware", "KEHL", "eisenbahn05")
const res = db_remote.execute("SELECT * FROM RESULTOBJEKT")
console.log(res);
db_remote.close();

nexusdb.unloadDll();
