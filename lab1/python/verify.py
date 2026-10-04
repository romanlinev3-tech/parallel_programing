from pathlib import Path
import sys

try:
    import numpy as np
except ImportError:
    print("ERROR: NumPy is not installed.")
    print("Install it with: python -m pip install numpy")
    sys.exit(1)

ROOT = Path(__file__).resolve().parents[1]

A_FILE = ROOT / "data" / "matrix_a.txt"
B_FILE = ROOT / "data" / "matrix_b.txt"
RESULT_FILE = ROOT / "data" / "result.txt"


def read_matrix(path: Path) -> np.ndarray:
    with path.open("r", encoding="utf-8") as file:
        first_line = file.readline().strip()

        if not first_line:
            raise ValueError(f"Missing matrix size in {path}")

        n = int(first_line)
        values = []

        for line in file:
            values.extend(float(value) for value in line.split())

    if n <= 0:
        raise ValueError(f"Invalid matrix size in {path}")

    if len(values) != n * n:
        raise ValueError(
            f"Expected {n * n} values in {path}, "
            f"but found {len(values)}"
        )

    return np.array(values, dtype=float).reshape(n, n)


def main() -> int:
    try:
        a = read_matrix(A_FILE)
        b = read_matrix(B_FILE)
        actual = read_matrix(RESULT_FILE)

        if a.shape != b.shape:
            print("VERIFICATION FAILED: input dimensions differ.")
            return 1

        expected = a @ b

        if actual.shape != expected.shape:
            print(
                "VERIFICATION FAILED: result dimensions differ."
            )
            return 1

        if np.allclose(actual, expected, rtol=1e-9, atol=1e-9):
            print("VERIFICATION PASSED")
            print(
                f"Matrix size: {a.shape[0]} x {a.shape[1]}"
            )
            print(
                "C++ result matches independent NumPy calculation."
            )
            return 0

        difference = np.max(np.abs(actual - expected))

        print("VERIFICATION FAILED")
        print(
            f"Maximum absolute difference: {difference}"
        )
        return 1

    except (OSError, ValueError) as error:
        print(f"VERIFICATION ERROR: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
