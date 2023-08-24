const nexusDb = require("./../build/Release/nexusdb.node");

console.log(nexusDb);
nexusDb.loadDll(__dirname + "/../nexusdb-lib/Win64/Debug/Project1.dll");

const db_id = nexusDb.addRemoteDatabase()
console.log(db_id);

nexusDb.closeDatabase(db_id);

nexusDb.unloadDll();
