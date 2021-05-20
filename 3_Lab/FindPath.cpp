class fifteen
{
private:
    int puzzle[16];
    enum eDirection
    {
        D_UP,
        D_DOWN,
        D_LEFT,
        D_RIGHT
    };

public:

    fifteen(int arr[])
    {
        for (int i=0; i<16; i++)
            puzzle[i]=arr[i];
    }

    bool isSolvable()
    {
        int parity = 0;
        int width = 4;
        int row = 0;
        int zeroRow = 0;

        for (int i = 0; i < 16; ++i)
        {
            if (i % width == 0)
            {
                row++;
            }

            if (puzzle[i] == 0)
            {
                zeroRow = row;
                continue;
            }
            for (int j = i + 1; j < 16; j++)
            {
                if (puzzle[i] > puzzle[j] && puzzle[j] != 0)
                {
                    parity++;
                }
            }
        }

        if (width % 2 == 0)
        { // even grid
            if (zeroRow % 2 == 0)
            { // blank on odd row; counting from bottom
                return parity % 2 == 0;
            } else
            { // blank on even row; counting from bottom
                return parity % 2 != 0;
            }
        } else
        { // odd grid
            return parity % 2 == 0;
        }
    }




};