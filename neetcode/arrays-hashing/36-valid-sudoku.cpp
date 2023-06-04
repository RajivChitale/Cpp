class Solution {

public:
    bool isValidSudoku(vector<vector<char>>& board) {

        //rows
        for(int i=0; i<9; i++)
        {
            int count[9] = {0};
            for(int j=0; j<9; j++)
            {
                char c = board[i][j];
                if(c == '.') continue;
                if(count[c-'1']++ > 0){return false;}
                // if digit, if repeated -> false, also increment count
            }
        }

        //cols
        for(int j=0; j<9; j++)
        {
            int count[9] = {0};
            for(int i=0; i<9; i++)
            {
                char c = board[i][j];
                if(c == '.') continue;
                if(count[c-'1']++ > 0){return false;}
                // if digit, if repeated -> false, also increment count
            }
        }

        //box
        for(int i=0; i<9; i+=3)
        {
         for(int j=0; j<9; j+=3)
         {
            int count[9] = {0};
            for(int inner=0; inner<9; inner++)
            {
                char c = board[i+inner/3][j+inner%3];
                if(c == '.') continue;
                if(count[c-'1']++ > 0){return false;}    
            }    
         }    
        }
        return true;
    }
};
