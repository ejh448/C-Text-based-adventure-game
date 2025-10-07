#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <random>

using namespace std;

/*
 All Moves:
    face_rotation_right:         complete
    face_rotation_left:          complete
    right_column_rotation_up:    complete
    right_column_rotation_down:  complete
    left_column_rotation_up:     complete
    left_column_rotation_down:   complete
    top_row_rotation_right:      complete
    top_row_rotation_left:       complete
    bottom_row_rotation_right:   complete
    bottomn_row_rotation_left:   complete
*/

class Cube{
    public:
        const int LENGTH = 3;
        int front[3][3];
        int top[3][3];
        int bottom[3][3];
        int back[3][3];
        int left[3][3];
        int right[3][3];
    
    Cube(){
        fill_face(front,  1);
        fill_face(top,    2);
        fill_face(back,   3);
        fill_face(bottom, 4);
        fill_face(left,   5);
        fill_face(right,  6);
    }

    void rotate_right(int face[3][3])
    {
        int temp[3][3];

        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                 temp[j][LENGTH - 1 - i] = face[i][j];
            }
        }

        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                face[i][j] = temp[i][j];
            }
        }
    }

    void rotate_left(int face[3][3])
    {
        int temp[3][3];
        
        for (int i = 0; i < LENGTH; i++)
        {
            for(int j = 0; j < LENGTH; j++)
            {
                temp[LENGTH - 1 - j][i] = face[i][j];
            }
        }

         for (int i = 0; i < LENGTH; i++)
        {
            for(int j = 0; j < LENGTH; j++)
            {
                face[i][j] = temp[i][j];
            }
        }
    }

    void right_column_up_rotation()
    {
        int temp_front[3];
        int temp_top[3];
        int temp_back[3];
        int temp_bottom[3];
        //NEED TO ROTATE RIGHT SIDE
        //cout << "\n";
        
        //ASSUMES FROM FRONT FACE
        for (int i = 0; i < LENGTH; i++)
        {
            //gets all on right side
            temp_front[i] = front[i][2];    // -> top
            temp_top[i] = top[i][2];        // -> back
            temp_back[i] = back[i][2];      // -> bottom
            temp_bottom[i] = bottom[i][2];  // -> front
        }
        
        //moves all right columns up one face
        for (int i = 0; i < LENGTH; i++)
        {
            top[i][2] = temp_front[i];
            back[i][2] = temp_top[i]; 
            bottom[i][2] = temp_back[i];
            front[i][2] = temp_bottom[i];
        }

        //need to rotate the right side
        rotate_right(right);

        //cout << "\nfront:\n", print_face(front), cout << "\ntop:\n", print_face(top), cout << "\nback:\n", print_face(back), cout << "\nbottom:\n", print_face(bottom);

    }

    void right_column_down_rotation()
    {
        int temp_front[3];
        int temp_top[3];
        int temp_back[3];
        int temp_bottom[3];

        for (int i = 0; i < LENGTH; i++)
        {
            //gets all on right side
            temp_front[i] = front[i][2];   // -> bottom
            temp_top[i] = top[i][2];       // -> front
            temp_back[i] = back[i][2];     // -> top
            temp_bottom[i] = bottom[i][2]; // -> back
        }

        for (int i = 0; i < LENGTH; i++)
        {
            top[i][2] = temp_back[i];
            back[i][2] = temp_bottom[i]; 
            bottom[i][2] = temp_front[i];
            front[i][2] = temp_top[i];
        }

        rotate_left(right);

        //cout << "\nfront:\n", print_face(front), cout << "\ntop:\n", print_face(top), cout << "\nback:\n", print_face(back), cout << "\nbottom:\n", print_face(bottom);


    }

    void left_column_up_rotation()
    {
        int temp_front[3];
        int temp_top[3];
        int temp_back[3];
        int temp_bottom[3];
        
        //cout << "\n";
        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[i][0];    // -> top
            temp_top[i] = top[i][0];        // -> back
            temp_back[i] = back[i][0];      // -> bottom
            temp_bottom[i] = bottom[i][0];  // -> front
        }

        //moves all right columns up one face
        for (int i = 0; i < LENGTH; i++)
        {
            top[i][0] = temp_front[i];
            back[i][0] = temp_top[i]; 
            bottom[i][0] = temp_back[i];
            front[i][0] = temp_bottom[i];
        }

        //need to rotate the right side
        rotate_left(left);
        //cout << "\nfront:\n", print_face(front), cout << "\ntop:\n", print_face(top), cout << "\nback:\n", print_face(back), cout << "\nbottom:\n", print_face(bottom);
    }

    void left_column_down_rotation()
    {
        int temp_front[3];
        int temp_top[3];
        int temp_back[3];
        int temp_bottom[3];

        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[i][0];    // -> bottom
            temp_top[i] = top[i][0];        // -> front
            temp_back[i] = back[i][0];      // -> top
            temp_bottom[i] = bottom[i][0];  // -> back
        }

        for (int i = 0; i < LENGTH; i++)
        {
            top[i][0] = temp_back[i];
            back[i][0] = temp_bottom[i]; 
            bottom[i][0] = temp_front[i];
            front[i][0] = temp_top[i];
        }
        
        rotate_right(left);
        
       // cout << "\nfront:\n", print_face(front), cout << "\ntop:\n", print_face(top), cout << "\nback:\n", print_face(back), cout << "\nbottom:\n", print_face(bottom);

    }

    void top_row_right_rotation()
    {
        int temp_front[3];
        int temp_left[3];
        int temp_right[3];
        int temp_back[3];

        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[0][i];    // -> left
            temp_left[i] = left[0][i];      // -> back
            temp_back[i] = back[0][i];      // -> right
            temp_right[i] = right[0][i];    // -> front
        }

        for (int i = 0; i < LENGTH; i++)
        {
            front[0][i] = temp_right[i];
            left[0][i] = temp_front[i]; 
            back[0][i] = temp_left[i];
            right[0][i] = temp_back[i];
        }
        
        rotate_right(top);
        
        //cout << "\nfront:\n", print_face(front), cout << "\nleft:\n", print_face(left), cout << "\nback:\n", print_face(back), cout << "\nright:\n", print_face(right);
    }

    void top_row_left_rotation()
    {
        int temp_front[3];
        int temp_left[3];
        int temp_right[3];
        int temp_back[3];

        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[0][i];    // -> right
            temp_left[i] = left[0][i];      // -> front
            temp_back[i] = back[0][i];      // -> left
            temp_right[i] = right[0][i];    // -> back
        }

        for (int i = 0; i < LENGTH; i++)
        {
            front[0][i] = temp_left[i];
            left[0][i] = temp_back[i]; 
            back[0][i] = temp_right[i];
            right[0][i] = temp_front[i];
        }
        
        rotate_left(top);
        
        //cout << "\nfront:\n", print_face(front), cout << "\nleft:\n", print_face(left), cout << "\nback:\n", print_face(back), cout << "\nright:\n", print_face(right);
    }

    void bottom_row_left_rotation()
    {
        int temp_front[3];
        int temp_left[3];
        int temp_right[3];
        int temp_back[3];

        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[2][i];    // -> right
            temp_left[i] = left[2][i];      // -> front
            temp_back[i] = back[2][i];      // -> left
            temp_right[i] = right[2][i];    // -> back
        }

            
        for (int i = 0; i < LENGTH; i++) {
            front[2][i] = temp_right[i];
            left[2][i]  = temp_front[i];
            back[2][i]  = temp_left[i];
            right[2][i] = temp_back[i];
        }

        rotate_right(bottom);
        
        //cout << "\nfront:\n", print_face(front), cout << "\nleft:\n", print_face(left), cout << "\nback:\n", print_face(back), cout << "\nright:\n", print_face(right);
    }

    void bottom_row_right_rotation()
    {
        int temp_front[3];
        int temp_left[3];
        int temp_right[3];
        int temp_back[3];

        for (int i = 0; i < LENGTH; i++)
        {
            temp_front[i] = front[2][i];    // -> right
            temp_left[i] = left[2][i];      // -> front
            temp_back[i] = back[2][i];      // -> left
            temp_right[i] = right[2][i];    // -> back
        }

        for (int i = 0; i < LENGTH; i++) {
            front[2][i] = temp_left[i];
            left[2][i]  = temp_back[i];
            back[2][i]  = temp_right[i];
            right[2][i] = temp_front[i];
        }
        
        rotate_left(bottom);
        
        //cout << "\nfront:\n", print_face(front), cout << "\nleft:\n", print_face(left), cout << "\nback:\n", print_face(back), cout << "\nright:\n", print_face(right);
    }

    void fill_face(int face[3][3], int value)
    {
        for(int i = 0; i < LENGTH; i++)
        {
            for(int j = 0; j < LENGTH; j++)
            {
                face[i][j] = value;
            }
        }
    }

    void fill_all_9(int face[3][3])
    {
        int x = 0;
        for(int i = 0; i < LENGTH; i++)
        {
            for(int j = 0; j < LENGTH; j++)
            {
                face[i][j] = x;
                x++;
            }
        }
    }

    void print_face(int face[3][3])
    {
         for(int i = 0; i < LENGTH; i++)
        {
            cout << "\n";
            for(int j = 0; j < LENGTH; j++)
            {
                cout << face[i][j];
            }
        }
        cout << "\n";
    }

    bool check_face(int face[3][3])
    {
        int check = face[1][1]; //middle block
        //cout << "check :" << check << "\n";
        for (int i = 0; i < LENGTH; i++)
        {
             for (int j = 0; j < LENGTH; j++)
            {
                if (face[i][j] != check)
                {
                    //cout << "\nFALSE\n";
                    return false;
                }
            }
        }
        //cout << "\nTRUE\n";
        return true;
    }

    bool check_cross(int face[3][3])
    {
        int check = face[1][1]; //middle block
        if (face[0][1] == check && face[1][0] == check && face[2][1] == check && face[1][2] == check)
        {
            return true;
        }
        return false;
    }

    void manual_insert_faces()
    {
        int answer;
        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter front face: " << i << ":" << j << "\n";
                cin >> answer;
                front[i][j] = answer;
            }
        }
        //check_face(front);

        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter left face: " << i << ":" << j << "\n";
                cin >> answer;
                left[i][j] = answer;
            }
        }

        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter back face: " << i << ":" << j << "\n";
                cin >> answer;
                back[i][j] = answer;
            }
        }

         for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter right face: " << i << ":" << j << "\n";
                cin >> answer;
                right[i][j] = answer;
            }
        }

         for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter top face: " << i << ":" << j << "\n";
                cin >> answer;
                top[i][j] = answer;
            }
        }

         for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                cout << "Please Enter bottom face: " << i << ":" << j << "\n";
                cin >> answer;
                bottom[i][j] = answer;
            }
        }
        cout << "\nfront:\n", print_face(front), cout << "\ntop:\n", print_face(top), cout << "\nback:\n", print_face(back), cout << "\nbottom:\n", print_face(bottom), cout << "\nleft:\n", print_face(left), cout << "\right:\n", print_face(right);
    }

    void solve_cross()
    {
        bool solved = false;
        cout << solved;
       
        random_device random_seed;                       // Seed
        mt19937 gen(random_seed());                      // Random generator
        uniform_int_distribution<> dis(1, 8);  // Numbers 1 to 9
        while (!solved)
        {
            int move = dis(gen);
            switch (move) {
                case 1: top_row_left_rotation(); cout << "left"; break;
                case 2: top_row_right_rotation(); break;
                case 3: bottom_row_left_rotation(); break;
                case 4: bottom_row_right_rotation(); break;
                case 5: right_column_down_rotation(); break;
                case 6: right_column_up_rotation(); break;
                case 7: left_column_up_rotation(); break;
                case 8: left_column_down_rotation(); break;
                default: break;
            }
            //solved = check_face(front) && check_face(left) && check_face(back) &&
            //        check_face(right) && check_face(top) && check_face(bottom);
            solved = check_cross(front);
        }
        cout << "solved!!!!!\n";
        print_face(front);
    }
};
    
int main()
{
    Cube cube;

// Front
cube.front[0][0]=2; cube.front[0][1]=1; cube.front[0][2]=3;
cube.front[1][0]=6; cube.front[1][1]=1; cube.front[1][2]=5;
cube.front[2][0]=4; cube.front[2][1]=2; cube.front[2][2]=3;

// Back
cube.back[0][0]=3; cube.back[0][1]=6; cube.back[0][2]=4;
cube.back[1][0]=5; cube.back[1][1]=3; cube.back[1][2]=2;
cube.back[2][0]=1; cube.back[2][1]=6; cube.back[2][2]=1;

// Left
cube.left[0][0]=5; cube.left[0][1]=2; cube.left[0][2]=4;
cube.left[1][0]=1; cube.left[1][1]=5; cube.left[1][2]=6;
cube.left[2][0]=3; cube.left[2][1]=2; cube.left[2][2]=1;

// Right
cube.right[0][0]=6; cube.right[0][1]=3; cube.right[0][2]=1;
cube.right[1][0]=4; cube.right[1][1]=6; cube.right[1][2]=2;
cube.right[2][0]=5; cube.right[2][1]=1; cube.right[2][2]=4;

// Top
cube.top[0][0]=2; cube.top[0][1]=4; cube.top[0][2]=5;
cube.top[1][0]=1; cube.top[1][1]=2; cube.top[1][2]=6;
cube.top[2][0]=3; cube.top[2][1]=5; cube.top[2][2]=1;

// Bottom
cube.bottom[0][0]=4; cube.bottom[0][1]=6; cube.bottom[0][2]=3;
cube.bottom[1][0]=2; cube.bottom[1][1]=4; cube.bottom[1][2]=1;
cube.bottom[2][0]=5; cube.bottom[2][1]=3; cube.bottom[2][2]=2;
    cube.solve_cross();
    return 0;
}


