#include <iostream>
struct Matrix
{
    int **data;
    int size;
    Matrix(int size)
    {
        this->size = size;
        data = new int *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new int[size];
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] = 0;
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
    Matrix(const Matrix &other)
    {
        size = other.size;
        data = new int *[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = new int[size];
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    Matrix add(const Matrix &other) const
    {
        Matrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    Matrix sub(const Matrix &other) const
    {
        Matrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    Matrix naiveMultiply(const Matrix &other) const
    {
        Matrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
    Matrix mul(const Matrix &other) const
    {
        if (size <= 2)
        {
            return naiveMultiply(other);
        }
        else if (size % 2 != 0)
        {
            Matrix A(size + 1);
            Matrix B(size + 1);
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    A.data[i][j] = data[i][j];
                    B.data[i][j] = other.data[i][j];
                }
            }
            return A.mul(B);
        }
        else
        {        
            Matrix result(size);

            Matrix A(size / 2);
            Matrix B(size / 2);
            Matrix C(size / 2);
            Matrix D(size / 2);
            Matrix E(size / 2);
            Matrix F(size / 2);
            Matrix G(size / 2);
            Matrix H(size / 2);
            for (int i = 0; i < size / 2; i++)
            {
                for (int j = 0; j < size / 2; j++)
                {
                    A.data[i][j] = data[i][j];
                }
            }
            for (int i = 0; i < size / 2; i++)
            {
                for (int j = size / 2; j < size; j++)
                {
                    B.data[i][j - size / 2] = data[i][j];
                }
            }
            for (int i = size / 2; i < size; i++)
            {
                for (int j = 0; j < size / 2; j++)
                {
                    C.data[i - size / 2][j] = data[i][j];
                }
            }
            for (int i = size / 2; i < size; i++)
            {
                for (int j = size / 2; j < size; j++)
                {
                    D.data[i - size / 2][j - size / 2] = data[i][j];
                }
            }
            for (int i = 0; i < size / 2; i++)
            {
                for (int j = 0; j < size / 2; j++)
                {
                    E.data[i][j] = other.data[i][j];
                }
            }
            for (int i = 0; i < size / 2; i++)
            {
                for (int j = size / 2; j < size; j++)
                {
                    F.data[i][j - size / 2] = other.data[i][j];
                }
            }
            for (int i = size / 2; i < size; i++)
            {
                for (int j = 0; j < size / 2; j++)
                {
                    G.data[i - size / 2][j] = other.data[i][j];
                }
            }
            for (int i = size / 2; i < size; i++)
            {
                for (int j = size / 2; j < size; j++)
                {
                    H.data[i - size / 2][j - size / 2] = other.data[i][j];
                }
            }
            Matrix S1(F.sub(H));
            Matrix S2(A.add(B));
            Matrix S3(C.add(D));
            Matrix S4(G.sub(E));
            Matrix S5(A.add(D));
            Matrix S6(E.add(H));
            Matrix S7(B.sub(D));
            Matrix S8(G.add(H));
            Matrix S9(A.sub(C));
            Matrix S10(E.add(F));
            Matrix P1(A.mul(S1));
            Matrix P2(S2.mul(H));
            Matrix P3(S3.mul(E));
            Matrix P4(D.mul(S4));
            Matrix P5(S5.mul(S6));
            Matrix P6(S7.mul(S8));
            Matrix P7(S9.mul(S10));
            Matrix C11((P5.add(P4)).sub(P2).add(P6));
            Matrix C12(P1.add(P2));
            Matrix C21(P3.add(P4));
            Matrix C22((P5.add(P1)).sub(P3).sub(P7));
            // C11.print();
            for (int i = 0; i < size / 2; i++)
            {
                for (int j = 0; j < size / 2; j++)
                {
                    result.data[i][j] = C11.data[i][j];
                    result.data[i][j + size / 2] = C12.data[i][j];
                    result.data[i + size / 2][j] = C21.data[i][j];
                    result.data[i + size / 2][j + size / 2] = C22.data[i][j];
                }
            }
            return result;
        }
    }
    void print() const
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
int main()
{
    int n;
    std::cin >> n;
    Matrix A(n);
    Matrix B(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> A.data[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> B.data[i][j];
        }
    }
    Matrix C = A.mul(B);
    C.print();
    return 0;
}