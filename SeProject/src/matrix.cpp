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

matrix::matrix(string s)
{

	 this->rows=matrix::Getrows(s) ;
     this->columns=matrix::Getcolumns(s) ;
     this->s=s;
   	 mat=matrix::create_matrix(rows,columns);
   	 mat=matrix::fill_matrix(s, mat, rows, columns);

}
matrix::matrix(int rows , int columns)
{

	this->rows =rows;
	this->columns = columns;
	mat = matrix::createEmptyMatrix(rows, columns);

}

/*
void matrix::copy_matrix(matrix &m)
{
this->rows=m.rows;
this->columns=m.columns;
float** matrix = new float*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix [i] = new float[columns];

		for(int j=0 ;j<columns;j++)
        {
              matrix[i][j] = m.mat[i][j];
        }
	}
} */


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

matrix matrix::sum_matrix(matrix &A, matrix& B)
{

	matrix result (B.rows, A.columns);

	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.columns; j++)
		{
			result.mat[i][j] = A.mat[i][j] + B.mat[i][j];
		}
	}

	return result;
}



matrix matrix::sub_matrix(matrix &A, matrix& B)
	{
        matrix result (A.rows, A.columns);

		for (int i = 0; i < A.rows; i++)
		{
			for (int j = 0; j < A.columns; j++)
			{
				result.mat[i][j] = A.mat[i][j] - B.mat[i][j];
			}
		}

		return result;
	}


matrix matrix::multiply_matrix(matrix &A, matrix &B)
	{
		matrix result (A.rows, A.columns);

		for (int i = 0; i < A.rows; i++)
		{
			for (int j = 0; j < B.columns; j++)
			{
				for (int k = 0; k < B.rows; k++)
					result.mat[i][j] += A.mat[i][k] * B.mat[k][j];
			}
		}

		return result;
	}
	//////////////////////////////////partial pivoting/////////////////////////////////////////////////

matrix matrix::partial_pivoting (matrix C ,int rows ,int i)
    {
		
        float dummy ;

       for (int k = rows - 1; k > i; k--)
	   {
		  if (C.mat[k - 1][i] < C.mat[k][i])
		  for (int j = 0; j < rows * 2; j++)
		  {
			dummy = C.mat[k][j];
			C.mat[k][j] = C.mat[k - 1][j];
			C.mat[k - 1][j] = dummy;
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

matrix matrix::divide_matrix (matrix & A,matrix&B)
	{
    
		if(A.rows!=columns ||B.rows!=B.columns||A.rows!=B.rows)
            {
                    throw("these two matrices can not be divided , the martix must be squared \n");

            }
	    ////////creating inverse///////
         int i, j, k;
	     float r;

		 matrix result(B.rows,B.columns);

		
              //creating larger matrix

		 matrix C(B.rows, 2 * B.columns);

		//filling larger matrix

		for ( i=0;i<B.rows;i++)
        {
            for( j=0 ;j<B.columns;j++)
            {
				C.mat[i][j] = B.mat[i][j];
            }
            for(j= B.columns;j<2*B.columns;j++)
            {
                if (j==i+B.rows)
                C.mat[i][j]=1; //filling the diagonals of identity matrix with 1

            }
        }

	//////////////////////////////////diagonal matrix/////////////////////////////////////////////////

	for (i = 0; i < B.rows; i++) //choose pivot element from every row ..row by row and make the following
	{

       C=partial_pivoting(C,B.rows,i); //re_arrange the elements below every pivot

		for (j = 0; j < B.rows ; j++) //iterate over all the rows row by row and make the following

        if (j != i) //to not include diagonals
		{
			r= C.mat[j][i] / C.mat[i][i];
			//r = C[j][i] / C[i][i]; //[i][i]  eldiagonal ,
			//kol row b3mlo nae2s elrow elly fo2 mdroob f elfactor elly ysfre elly 3lgnb


			for (k = 0; k < B.rows * 2; k++) //iterate over every column of a specefic row ..element by element and make this operation
				C.mat[j][k] -= C.mat[i][k] * r;
        }

	}

    //////////////////////////////////unit matrix/////////////////////////////////////////////////
	for (i = 0; i < B.rows; i++)
	{
		r = C.mat[i][i]; //diagonals
		for (j = 0; j < B.rows * 2; j++)
			C.mat[i][j] = C.mat[i][j] / r; //hdfy 2ny a5ly eldiagonals bw7aied

	}

	for (i = 0; i < B.rows; i++) //transfer the result
	{
		for (j = B.rows; j < B.rows * 2; j++) //5lly balek 2na hna ba5od elgoz2 elly 3lgnb elymin bs
			result.mat[i][j - B.rows] = C.mat[i][j];

	}

	result = multiply_matrix(A, result);
  
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

