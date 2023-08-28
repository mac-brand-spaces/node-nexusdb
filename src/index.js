var lib

if (process.platform !== "win32") {
  throw new Error("NexusDB: Only Windows is supported")
} else {
  const { join } = require("path")
  if (process.arch === "x64") {
    lib = require(join(__dirname, "..", "bin", "nexusdb-x64.node"))
  } else if (process.arch === "x32") {
    lib = require(join(__dirname, "..", "bin", "nexusdb-x32.node"))
  } else {
    throw new Error("NexusDB: Unsupported architecture")
  }
}

/**
 * @function loadDll
 * @param {string} path
 * @returns {void}
 * @description loads the nexusdb.dll
 * @example loadDll("./nexusdb.dll");
 */
function loadDll(path = undefined) {
  if (path === undefined) {
    const { join } = require("path")
    const { existsSync } = require("fs")
    path = join(__dirname, "..", "lib", "nexusdb.dll")
    if (!existsSync(path)) {
      path = join(__dirname, "..", "nexusdb.dll")
      if (!existsSync(path)) {
        path = join(
          __dirname,
          "..",
          "nexusdb-lib",
          "Win64",
          "Debug",
          "Project1.dll"
        )
        if (!existsSync(path)) {
          throw new Error("NexusDB: Failed to find nexusdb.dll")
        }
      }
    }
  }
  lib.loadDll(path)
}

/**
 * unloads the nexusdb.dll
 * @function unloadDll
 * @param {string} path
 * @returns {void}
 * @description unloads the nexusdb.dll
 * @example unloadDll();
 */
function unloadDll() {
  lib.unloadDll()
}

class NexusDb {
  /**
   * @private
   * @type {string}
   */
  _id = undefined
  /**
   * @private
   * @type {object}
   */
  _info = undefined
  /**
   * @private
   * @type {boolean}
   * @description Whether the database is closed or not
   * @default false
   */
  _closed = false

  /**
   * @function execute
   * @param {string} query
   * @param {object} params
   * @returns {object[]}
   * @description Executes a query on the database
   * @example const result = await db.execute("SELECT * FROM users WHERE id = :id", { id: 1 });
   */
  execute(query, params = undefined) {
    if (this._closed) {
      throw new Error("NexusDB: Database already closed")
    }
    const params_str = JSON.stringify(params || {})
    const str_result = lib.execute(this._id, query, params_str)
    var result
    try {
      result = JSON.parse(str_result)
    } catch (e) {
      throw new Error("NexusDB: Failed to parse result")
    }
    if (result.status === "error") {
      if (result.error) {
        throw new Error(`NexusDB: ${result.error}`)
      }
      throw new Error("NexusDB: Unknown error")
    }
    if (result.status === "success") {
      return result.result
    }
  }

  /**
   * @function close
   * @returns {void}
   * @description Closes the database connection
   * @example await db.close();
   */
  close() {
    if (this._closed) {
      throw new Error("NexusDB: Database already closed")
    }
    const success = lib.closeDatabase(this._id)
    if (success) {
      this._closed = true
      return
    }
    throw new Error("NexusDB: Failed to close database")
  }
}

/**
 * @function NexusRemoteDatabase
 * @param {string} host
 * @param {string} alias
 * @param {string} username
 * @param {string} password
 * @returns {NexusDb}
 * @description Creates a new remote database connection
 */
function NexusRemoteDatabase(host, alias, username, password) {
  const info_str = lib.addRemoteDatabase(host, alias, username, password)
  var info
  try {
    info = JSON.parse(info_str)
  } catch (e) {
    throw new Error("NexusDB: Failed to parse info")
  }
  const db = new NexusDb()
  db._id = info.id
  db._info = info
  return db
}

/**
 * @function NexusLocalDatabase
 * @param {string} path
 * @param {string} alias
 * @returns {NexusDb}
 * @description Creates a new local database connection
 */
function NexusLocalDatabase(path, alias) {
  const info_str = lib.addDatabase(path, alias)
  var info
  try {
    info = JSON.parse(info_str)
  } catch (e) {
    throw new Error("NexusDB: Failed to parse info")
  }
  const db = new NexusDb()
  db._info = info
  db._id = db._info.id
  return db
}

module.exports = {
  loadDll,
  unloadDll,
  NexusRemoteDatabase,
  NexusLocalDatabase,
}
