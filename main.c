#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 3

// Function Declarations
int encryption_matrix();
int matrix_multiplication();
int determinant(int matrix2[3][3]);
void cofactor_matrix(int matrix2[SIZE][SIZE], int cofactor[SIZE][SIZE]);
void adjoint_matrix(int cofactor[SIZE][SIZE], int adjoint[SIZE][SIZE]);
void inverse_matrix(int adjoint[SIZE][SIZE], int det);
int og_matrix();
void reconstructing_the_og_message();

int message_matrix[3][3];
int matrix2[3][3]; 
int cofactor[3][3];
int adjoint[3][3];
int inverse[3][3];
static int result_matrix[3][3];
char reconstructed_message[9];
int result_matrix2[3][3];


int main() {
    char private_message[9] = "bananana";
    
    int y = 0;
    srand(time(0));

    // Convert the private message to an integer matrix (message_matrix)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            message_matrix[i][j] = (int)private_message[y];
            y++;
        }
    }

    // Display the message matrix
    printf("Message Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", message_matrix[i][j]);
        }
        printf("\n");
    }
    matrix2[0][0]=1;
    matrix2[0][1]=2;
    matrix2[0][2]=3;
    matrix2[1][0]=0;
    matrix2[1][1]=1;
    matrix2[1][2]=4;
    matrix2[2][0]=0; 
    matrix2[2][1]=0;
    matrix2[2][2]=1;

    // Generate and display the encryption matrix
    printf("\nEncryption Matrix:\n");
    encryption_matrix();

    // Calculate and display the determinant of matrix2
    int det = determinant(matrix2);
    printf("The value of determinant of matrix2 is: %d\n", det);

    // Check if determinant is 0 (singular matrix)
    if (det == 0) {
        printf("The matrix is singular and does not have an inverse.\n");
        exit(0);  // Exit if the matrix is singular
    }

    // Matrix multiplication and display
    printf("\nResult of matrix multiplication:\n");
    matrix_multiplication();

    // Compute and display the cofactor matrix
    printf("\nThe cofactor matrix is:\n");
    cofactor_matrix(matrix2, cofactor);

    // Compute and display the adjoint matrix
    printf("\nThe adjoint matrix is:\n");
    adjoint_matrix(cofactor, adjoint);

    // Compute and display the inverse matrix
    inverse_matrix(adjoint, det);
    og_matrix(inverse,result_matrix);
    printf("The reconstructed string is \n");
    reconstructing_the_og_message(result_matrix2);

    return 0;
}

// Function to generate encryption matrix (simple example)
int encryption_matrix() {
    

    // Display the encryption matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", matrix2[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Function to perform matrix multiplication (message_matrix * matrix2)
// result_matrix is used to store the result of multiplication without affecting matrix2
int matrix_multiplication() {
     // This will store the multiplication result

    // Perform the matrix multiplication
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result_matrix[i][j] += message_matrix[i][k] * matrix2[k][j];
            }
        }
    }

    // Display the result of matrix multiplication (stored in result_matrix)
    printf("\nResulting Matrix from Multiplication:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", result_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Function to calculate the determinant of a 3x3 matrix
int determinant(int matrix2[3][3]) {
    int det = 0;
    // Calculate determinant using the rule for a 3x3 matrix
    for (int i = 0; i < SIZE; i++) {
        det += matrix2[0][i] * (matrix2[1][(i + 1) % SIZE] * matrix2[2][(i + 2) % SIZE] - matrix2[1][(i + 2) % SIZE] * matrix2[2][(i + 1) % SIZE]);
    }
    return det;
}

// Function to calculate the cofactor matrix of a 3x3 matrix using loops
void cofactor_matrix(int matrix2[SIZE][SIZE], int cofactor[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Calculate the determinant of the 2x2 submatrix by removing row i and column j
            int submatrix[2][2];
            int x = 0, y = 0;
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    if (row != i && col != j) {
                        submatrix[x][y] = matrix2[row][col];
                        y++;
                        if (y == 2) {
                            y = 0;
                            x++;
                        }
                    }
                }
            }
            // Calculate the determinant of the 2x2 submatrix
            int minor = submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0];
            // Apply cofactor formula: (-1)^(i+j) * minor
            cofactor[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor;
        }
    }
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%d ", cofactor[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the adjoint matrix (transpose of cofactor matrix)
void adjoint_matrix(int cofactor[SIZE][SIZE], int adjoint[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            adjoint[i][j] = cofactor[j][i];  // Transpose the cofactor matrix
        }
    }
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%d ", adjoint[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate the inverse matrix (adjoint / determinant)
void inverse_matrix(int adjoint[SIZE][SIZE], int det) {
    printf("\nInverse Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inverse[i][j]=(adjoint[i][j]/det);
            printf("%d\t", inverse[i][j]);
        }
        printf("\n");
    }
}
int og_matrix(int inverse[3][3],int result_matrix[3][3]){
     // This will store the multiplication result

    // Perform the matrix multiplication
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result_matrix2[i][j] += result_matrix[i][k] * inverse[k][j];
            }
        }
    }

    // Display the result of matrix multiplication (stored in result_matrix)
    printf("\nResulting og_Matrix from Multiplication:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", result_matrix2[i][j]);
        }
        printf("\n");
    }
    return 0;
    
}
void reconstructing_the_og_message(int result_matrix2[3][3]){
    int index=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            reconstructed_message[index++]=(char)result_matrix2[i][j];
            
        }
    }
    reconstructed_message[index]='\0';
    printf("%s",reconstructed_message);
    
}
