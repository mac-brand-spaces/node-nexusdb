declare module "nexusdb" {
  export function loadDll(path: string): void;
  export function unloadDll(): void;

  export class NexusDb {
    private _id: string | undefined;
    private _info: object | undefined;
    private _closed: boolean;

    execute(query: string, params: object): Promise<object>;
    close(): void;
  }
}
