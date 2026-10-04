from pathlib import Path
import sys

try:
    import numpy as np
except ImportError:
    print("ERROR: NumPy is not installed.")
    print("Install it with: pip install numpy")
    sys.exit(1)

ROOT = Path(__file__).resolve().parents[1]
A_FILE = ROOT / "data" / "matrix_a.txt"
B_FILE = ROOT / "data" / "matrix_b.txt"
RESULT_FILE = ROOT / "data" / "result.txt"


def read_matrix(path: Path) -> np.ndarray:
    with path.open("r", encoding="utf-8") as file:
        n = int(file.readline().strip())
        values = []
        for line in file:
            values.extend(float(x) for x in line.split())

    if len(values) != n * n:
        raise ValueError(f"Invalid matrix size in {path}")

    return np.array(values, dtype=float).reshape((n, n))


def main() -> int:
    a = read_matrix(A_FILE)
    b = read_matrix(B_FILE)
    actual = read_matrix(RESULT_FILE)

    expected = a @ b

    if actual.shape != expected.shape:
        print("VERIFICATION FAILED: matrix dimensions differ.")
        return 1

    if np.allclose(actual, expected, rtol=1e-9, atol=1e-9):
        print("VERIFICATION PASSED")
        print(f"Matrix size: {a.shape[0]} x {a.shape[1]}")
        print("C++ result matches NumPy result.")
        return 0

    difference = np.max(np.abs(actual - expected))
    print("VERIFICATION FAILED")
    print(f"Maximum absolute difference: {difference}")
    print("Expected:")
    print(expected)
    print("Actual:")
    print(actual)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
