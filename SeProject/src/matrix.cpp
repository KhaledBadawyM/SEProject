/*
 * matrix.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: m_eltobgy
 */

#include "matrix.h"

matrix::matrix() {
	 rows = 0;
   	 columns = 0;
   	 matr=NULL;
}

/*
void matrix::copy_matrix(int rows,int columns,)
{

this->rows=m.rows;
this->columns=m.columns;

float** matrix = new float*[rows];

	for (int i = 0; i < rows; i++)
	{
		matrix [i] = new float[columns];

		for(int j=0 ;j<columns;j++)
        {
              matrix[i][j] = m.matr[i][j];

        }
	}



}

*/
matrix::~matrix() {
	// TODO Auto-generated destructor stub
}


int matrix:: Getrows(string s)
{
   		int rows;
		int postion = s.find("[");        // if martrix is empty ... so return rows =0
		s = s.substr(postion + 1);
		s = s.erase(s.length() - 1);
		if (s.length() == 0)
			return rows = 0;

		rows = count(s.begin(), s.end(), ';') + 1;
		return rows;
}

int matrix:: Getcolumns(string s)
{

        int columns;
		string s1;
		int postion = s.find("[");
		          // if martrix is empty ... so return columns =0
		int place=s.find(";");
		
		s1 = s.substr(postion,place-postion);
        columns = (count(s1.begin(), s1.end(),' ') + 1);
	
	
		return columns;
}

float** matrix::create_matrix(int rows, int columns)     //MUST initialize all values to zero
{

	float** matrix = new float*[rows];

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new float[columns];
	}

	return matrix;
}

void matrix::destroy_matrix(float** matrix, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i]; //deletes an inner array of integer;
	}

	delete[] matrix; //delete pointer holding array of pointers;
}



float** matrix::fill_matrix(string s, float** A, int rows, int columns)
{
    while(s.find(";")!=-1)
{
    if(s.substr(s.find(";")+1,1) ==" ")
    {
          s.erase(s.find(";"),1);
    }
    else
    {
        s.insert(s.find(";")+1,1,' ');
        s.erase(s.find(";"),1);
    }

}

    s.erase(s.find('['),1);
    s.erase(s.find(']'),1);

    stringstream stream ;
    stream << s;

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            stream>>A[i][j];
        }
    }
	return A;
}

float**matrix::createEmptyMatrix(int rows, int columns)
{
	float** result = new float*[rows];

	for (int i = 0; i < rows; i++)
	{
		result[i] = new float[columns];
		memset(result[i], 0, columns * sizeof(float));       //to make every element NULL
	}

	return result;
}

matrix matrix::sum_matrix(matrix A, matrix B)
{

	matrix result = createEmptyMatrix(B.rows, A.columns);

	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.columns; j++)
		{
			result[i][j] = A[i][j] + B[i][j];
		}
	}

	return result;
}



matrix matrix::sub_matrix(matrix A, matrix B)
	{
        matrix result = createEmptyMatrix(A.rows, A.columns);

		for (int i = 0; i < A.rows; i++)
		{
			for (int j = 0; j < A.columns; j++)
			{
				result[i][j] = A[i][j] - B[i][j];
			}
		}

		return result;
	}


float** matrix::multiply_matrix(float** A, float** B, int rows, int columns,int n1)
{
	float** result = createEmptyMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			for (int k = 0; k < n1; k++)
				result[i][j] += A[i][k] * B[k][j];
		}
	}

	return result;
}
	//////////////////////////////////partial pivoting/////////////////////////////////////////////////

float** matrix::partial_pivoting (float ** C ,int rows ,int i)
    {
        float dummy ;

       for (int k = rows - 1; k > i; k--)
	   {
		  if (C[k - 1][i] < C[k][i])
		  for (int j = 0; j < rows * 2; j++)
		  {
			dummy = C[k][j];
			C[k][j] = C[k - 1][j];
			C[k - 1][j] = dummy;
		  }
	    }
        return C;
     }

float** matrix::division_By_One(float** A ,int rows ,int columns)
{
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[i][j] = 1/A[i][j];
			}
		}

		return result;

}

float** matrix::divide_matrix (float** A , float** B , int rows ,int columns,int n1)
	{
	    ////////creating inverse///////
         int i, j, k;
	     float r;

		float** result = createEmptyMatrix(rows, columns);

              //creating larger matrix

		float**  C  = createEmptyMatrix(rows, 2*columns);

		//filling larger matrix

		for ( i=0;i<rows;i++)
        {
            for( j=0 ;j<columns;j++)
            {

                C[i][j]=B[i][j];
            }
            for(j= columns;j<2*columns;j++)
            {
                if (j==i+rows)
                C[i][j]=1; //filling the diagonals of identity matrix with 1

            }
        }

	//////////////////////////////////diagonal matrix/////////////////////////////////////////////////

	for (i = 0; i < rows; i++) //choose pivot element from every row ..row by row and make the following
	{

        C=partial_pivoting(C,rows,i); //re_arrange the elements below every pivot

		for (j = 0; j < rows ; j++) //iterate over all the rows row by row and make the following

        if (j != i) //to not include diagonals
		{
			r = C[j][i] / C[i][i]; //[i][i]  eldiagonal ,
			//kol row b3mlo nae2s elrow elly fo2 mdroob f elfactor elly ysfre elly 3lgnb


			for (k = 0; k < rows * 2; k++) //iterate over every column of a specefic row ..element by element and make this operation
				C[j][k] -= C[i][k] * r;
        }

	}

    //////////////////////////////////unit matrix/////////////////////////////////////////////////
	for (i = 0; i < rows; i++)
	{
		r = C[i][i]; //diagonals
		for (j = 0; j < rows * 2; j++)
			C[i][j] = C[i][j] / r; //hdfy 2ny a5ly eldiagonals bw7aied

	}

	for (i = 0; i < rows; i++) //transfer the result
	{
		for (j = rows; j < rows * 2; j++) //5lly balek 2na hna ba5od elgoz2 elly 3lgnb elymin bs
			result[i][j - rows] = C[i][j];

	}


result = multiply_matrix( A, result, rows,columns,n1);


return result;
	}

float**matrix:: Transpose_matrix(float** A, int rows, int columns)
	{

		float** result = createEmptyMatrix(columns, rows);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[j][i] = A[i][j];
			}
		}
		return result;
	}

	float** matrix::zeros_matrix(int rows, int columns)
{
	float** result = createEmptyMatrix(rows, columns);            // matrix.cpp

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result[i][j] = 0;
		}
	}

	return result;
}

float** matrix::ones_matrix(int rows, int columns)
{
	float** result = createEmptyMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result[i][j] = 1;
		}
	}

	return result;
}

float** matrix::eye_matrix(int rows, int columns)
{
	float** result = createEmptyMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if(i!=j)
			result[i][j] = 0;
			else
			result[i][j] = 1;
		}
	}

	return result;
}

float** matrix::rand_matrix(int rows, int columns)
{
	float** result = createEmptyMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}

	return result;
}



float** matrix::Exponential(float** A ,int rows ,int columns)
{
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[i][j] = exp(A[i][j]);

			}
		}

		return result;

}


float** matrix::Log_Base10(float** A ,int rows ,int columns,int &negative_flag)
{
  negative_flag=0;
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
			    if (A[i][j]<0)
                    negative_flag=1;

				result[i][j] = log10(A[i][j]);

			}
		}

		return result;

}

float** matrix::Log_Base2(float** A ,int rows ,int columns,int &negative_flag)
{
    negative_flag=0;
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
			    if (A[i][j]<0)
                    negative_flag=1;
				result[i][j] = log2(A[i][j]);

			}
		}

		return result;

}


float** matrix::Natural_Log(float** A ,int rows ,int columns,int &negative_flag)
{
  negative_flag=0;

   float** result = createEmptyMatrix(rows, columns);


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
                 if (A[i][j]<0)
                 negative_flag=1;


				result[i][j] = log(A[i][j]);



			}
		}



		return result;


}




float** matrix::Sin_M(float** A ,int rows ,int columns)
{
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[i][j] = sin(A[i][j]);

			}
		}

		return result;

}

float** matrix::Cos_M(float** A ,int rows ,int columns)
{
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[i][j] = cos(A[i][j]);

			}
		}

		return result;

}

float** matrix::Tan_M(float** A ,int rows ,int columns)
{
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				result[i][j] = tan(A[i][j]);

			}
		}

		return result;

}
float** matrix::SquareRoot(float** A ,int rows ,int columns,int & negative_flag)
{
   negative_flag =0;
   float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
			    if (A[i][j]<0)
                    negative_flag=1;
				result[i][j] = pow(A[i][j],0.5);

			}
		}

		return result;

}




/*float** matrix::Power_the_matrix(float **A,float **B,int rows,int cloumns)
{
    float** result = createEmptyMatrix(rows, columns);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				for (int k = 0; k < columns; k++)
					result[i][j] += A[i][k] * B[k][j];
			}
		}

		return result;
}*/




void matrix::print_matrix(float** A, int rows, int columns)
	{

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
			    if(abs(A[i][j])<0.0001)
                printf("%d       \t",0);

			    else if(abs(A[i][j]-int(A[i][j]))<0.0001)
                printf("%.0f       \t", A[i][j]);

                else
                printf("%.4f   \t", A[i][j]);
			}
			printf ("\n");
		}
	}

