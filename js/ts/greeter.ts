// Tiny TypeScript module compiled by ts_project (tsc transpiler, type-checked).
export interface Greeter {
  readonly name: string;
  greet(): string;
}

export function makeGreeter(name: string): Greeter {
  return {
    name,
    greet: () => `Hello, ${name} from TypeScript!`,
  };
}

export function sum(values: readonly number[]): number {
  return values.reduce((acc, v) => acc + v, 0);
}
