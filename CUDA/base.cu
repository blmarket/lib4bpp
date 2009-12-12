// matrixVecMul.cu 
/* 
* Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.  
* 
* NOTICE TO USER:  
* 
* This source code is subject to NVIDIA ownership rights under U.S. and 
* international Copyright laws.  
* 
* NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
* CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
* IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
* REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
* MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.  
* IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
* OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
* OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
* OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE 
* OR PERFORMANCE OF THIS SOURCE CODE.  
* 
* U.S. Government End Users.  This source code is a "commercial item" as 
* that term is defined at 48 C.F.R. 2.101 (OCT 1995), consisting  of 
* "commercial computer software" and "commercial computer software 
* documentation" as such terms are used in 48 C.F.R. 12.212 (SEPT 1995) 
* and is provided to the U.S. Government only as a commercial end item.  
* Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
* 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
* source code with only those rights set forth herein.  
*/ 
 
// Header files 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
 
// Types 
typedef struct { 
    int width; 
    int height; 
    int pitch; 
    float* e; 
} Matrix; 
 
typedef struct { 
    int width; 
    int height; 
    int pitch; 
    double* e; 
} MatrixD; 
 
typedef struct { 
    int length; 
    float* e; 
} Vector; 
 
typedef struct { 
    int length; 
    double* e; 
} VectorD; 
 
 
// Forward declarations 
void    MatrixVectorMulOnHost(const Matrix, const Vector, VectorD); 
void    MatrixVectorMulOnDevice(const Matrix, const Vector, Vector, int, int); 
 
Matrix  AllocateMatrix(int, int, float); 
void    FreeMatrix(Matrix); 
MatrixD AllocateMatrixD(int, int); 
void    FreeMatrixD(MatrixD); 
 
Matrix  AllocateDeviceMatrix(const Matrix); 
void    FreeDeviceMatrix(Matrix); 
void    CopyToDeviceMatrix(Matrix, const Matrix); 
void    CopyFromDeviceMatrix(Matrix, const Matrix); 
 
Vector  AllocateVector(int, float); 
void    FreeVector(Vector); 
VectorD AllocateVectorD(int); 
void    FreeVectorD(VectorD); 
 
Vector  AllocateDeviceVector(const Vector); 
void    FreeDeviceVector(Vector); 
void    CopyToDeviceVector(Vector, const Vector); 
void    CopyFromDeviceVector(Vector, const Vector); 
 
bool    CheckDevice(); 
double  ComputeL2NormError(const Vector, const VectorD); 
// The main function does the following: 
// - It initializes a matrix M and a vector V with random values 
// - It computes the product M * V on the device and on the host 
// - It compares the two results by computing the L2-norm error 
// The goal of the exercise is to replace TODO by the right piece of code 
// so that the source code compiles and produces an error of 0 
// to machine precision (less than 1e-6) 
int main(void){ 
    if (CheckDevice() == false) { 
        printf("\nThere is no device supporting CUDA.\n"); 
        printf("\nPress ENTER to exit...\n"); 
        getchar(); 
        return -1; 
    } 
 
    // 
    int maxThreadsPerBlock = 512; // need to optimize 
    int numMultiprocessors = 16; // change for GPU specs 
 
    // Need to modify the configuration 
    int numThreadsPerBlock = maxThreadsPerBlock; 
    int numBlocks = 2 * numMultiprocessors; 
    int width = 20 * numThreadsPerBlock; 
    int height = 20 * numBlocks;         
 
 
    // Allocate and initialize the matrices 
    Matrix  M  = AllocateMatrix(width, height, 1); 
    Vector  V  = AllocateVector(width, 1); 
    Vector  W  = AllocateVector(height, 0); 
    VectorD Wh = AllocateVectorD(height); 
 
    // M * V on the device 
    MatrixVectorMulOnDevice(M, V, W, numBlocks, numThreadsPerBlock); 
 
    // M * V on the host 
    MatrixVectorMulOnHost(M, V, Wh); 
 
    // Compute and print the L2-norm error 
    double error = ComputeL2NormError(W, Wh); 
    if (error < 1e-6) 
        printf("Correct result (L2-norm error is %e).\n", error); 
    else 
        printf("Incorrect result (L2-norm error is %e).\n", error); 
 
    printf("\nPress ENTER to exit...\n"); 
    getchar(); 
 
    // Free matrices 
    FreeMatrix(M); 
    FreeVector(V); 
    FreeVector(W); 
    FreeVectorD(Wh); 
 
    return 0; 
} 
 
// Forward declaration of the matrix vector multiplication kernel 
__global__ void MatrixVectorMulKernel(const Matrix, const Vector, Vector); 
 
// Matrix vector multiplication on the device 
void MatrixVectorMulOnDevice(const Matrix M, const Vector V, Vector W, 
                             int numBlocks, int numThreadsPerBlock) 
{ 
    // Load M and V to the device 
    Matrix Md = AllocateDeviceMatrix(M); 
    CopyToDeviceMatrix(Md, M); 
    Vector Vd = AllocateDeviceVector(V); 
    CopyToDeviceVector(Vd, V); 
 
    // Allocate W on the device 
    Vector Wd = AllocateDeviceVector(W); 
    CopyToDeviceVector(Wd, W); // Clear memory 
 
    // Launch the device computation 
    int sharedMemoryByteSize = numThreadsPerBlock * sizeof(float); 
    MatrixVectorMulKernel<<<numBlocks, numThreadsPerBlock, sharedMemoryByteSize>>>(Md, Vd, Wd); 
 
    // Read W from the device 
    CopyFromDeviceVector(W, Wd); 
 
    // Free device matrices 
    FreeDeviceMatrix(Md); 
    FreeDeviceVector(Vd); 
    FreeDeviceVector(Wd); 
} 
 
// Get a matrix row 
__device__ float* GetMatrixRow(const Matrix M, int y){ 
    return &M.e[y * M.pitch]; 
} 
 
// Get a vector element 
__device__ float GetVectorElement(const Vector V, int x){ 
    return V.e[x]; 
} 
 
// Set a vector element 
__device__ void SetVectorElement(Vector V, int x, float value){ 
    V.e[x] = value; 
} 
 
// Matrix vector multiplication kernel called by MatrixVectorMulOnDevice() 
__global__ void MatrixVectorMulKernel(const Matrix M, const Vector V, Vector W){ 
    // Number of blocks 
    int numBlocks = gridDim.x; 
 
    // Block ID 
    int blockID = blockIdx.x; 
 
    // Number of threads per block 
    int numThreadsPerBlock = blockDim.x; 
 
    // Thread ID 
    int threadID = threadIdx.x; 
 
    // Number of threads per grid 
    int numThreads = numBlocks * numThreadsPerBlock; 
       
    // Each thread handles as many matrix rows as necessary 
    for (int y = blockID * numThreadsPerBlock + threadID; 
         y < M.height; 
         y += numThreads) 
    { 
 
        // Pointer to the matrix row handled by thread threadID 
        const float* row = GetMatrixRow(M, y); 
 
        // Compute dot product 
        float dotProduct = 0; 
        for (int x = 0; x < M.width; ++x) 
            dotProduct += row[x] * GetVectorElement(V, x); 
 
        // Write result to global memory 
        SetVectorElement(W, y, dotProduct); 
    } 
} 
 
// Matrix vector multiplication on the host in double precision 
void MatrixVectorMulOnHost(const Matrix M, const Vector V, VectorD W){  
    for (int i = 0; i < M.height; ++i) { 
        double dotProduct = 0; 
        for (int k = 0; k < M.width; ++k) { 
            double a = M.e[i * M.width + k]; 
            double b = V.e[k]; 
            dotProduct += a * b; 
        } 
        W.e[i] = dotProduct; 
    } 
} 
 
// Allocate a matrix with random float entries 
Matrix AllocateMatrix(int width, int height, float scale){ 
    Matrix M; 
    M.width  = width; 
    M.height = height; 
    M.pitch  = width; 
    int size = width * height; 
    M.e = (float*)malloc(sizeof(float) * size); 
    for (int i = 0; i < size; ++i) 
        M.e[i] = scale * (rand() / (float)RAND_MAX); 
    return M; 
} 
 
// Free a matrix 
void FreeMatrix(Matrix M){ 
    free(M.e); 
} 
 
// Allocate a matrix with double entries 
MatrixD AllocateMatrixD(int width, int height){ 
    MatrixD M; 
    M.width  = width; 
    M.height = height; 
    M.pitch  = width; 
    M.e = (double*)malloc(sizeof(double) * width * height); 
    return M; 
} 
 
// Free a matrix with double entries 
void FreeMatrixD(MatrixD M){ 
    free(M.e); 
} 
 
// Allocate a device matrix of same size as M 
Matrix AllocateDeviceMatrix(const Matrix M){ 
    Matrix Mdevice = M; 
    int size = M.width * M.height * sizeof(float); 
    cudaMalloc((void**)&Mdevice.e, size); 
    return Mdevice; 
} 
 
// Free a device matrix 
void FreeDeviceMatrix(Matrix M){ 
    cudaFree(M.e); 
} 
 
// Copy a host matrix to a device matrix 
void CopyToDeviceMatrix(Matrix Mdevice, const Matrix Mhost){ 
    int size = Mhost.width * Mhost.height * sizeof(float); 
    cudaMemcpy(Mdevice.e, Mhost.e, size, cudaMemcpyHostToDevice); 
} 
 
// Copy a device matrix to a host matrix 
void CopyFromDeviceMatrix(Matrix Mhost, const Matrix Mdevice){ 
    int size = Mdevice.width * Mdevice.height * sizeof(float); 
    cudaMemcpy(Mhost.e, Mdevice.e, size, cudaMemcpyDeviceToHost); 
} 
 
// Allocate a vector with random float entries 
Vector AllocateVector(int length, float scale){ 
    Vector V; 
    V.length  = length; 
    V.e = (float*)malloc(sizeof(float) * length); 
    for (int i = 0; i < length; ++i) 
        V.e[i] = scale * (rand() / (float)RAND_MAX); 
    return V; 
} 
 
// Free a vector 
void FreeVector(Vector V){ 
    free(V.e); 
} 
 
// Allocate a vector with double entries 
VectorD AllocateVectorD(int length){ 
    VectorD V; 
    V.length  = length; 
    V.e = (double*)malloc(sizeof(double) * length); 
    return V; 
} 
 
// Free a vector with double entries 
void FreeVectorD(VectorD V){ 
    free(V.e); 
} 
 
// Allocate a device vector of same size as V 
Vector AllocateDeviceVector(const Vector V){ 
    Vector Vdevice = V; 
    int size = V.length * sizeof(float); 
    cudaMalloc((void**)&Vdevice.e, size); 
    return Vdevice; 
} 
 
// Free a device vector 
void FreeDeviceVector(Vector V){ 
    cudaFree(V.e); 
} 
 
// Copy a host vector to a device vector 
void CopyToDeviceVector(Vector Vdevice, const Vector Vhost){ 
    int size = Vhost.length * sizeof(float); 
    cudaMemcpy(Vdevice.e, Vhost.e, size, cudaMemcpyHostToDevice); 
} 
 
// Copy a device vector to a host vector 
void CopyFromDeviceVector(Vector Vhost, const Vector Vdevice){ 
    int size = Vdevice.length * sizeof(float); 
    cudaMemcpy(Vhost.e, Vdevice.e, size, cudaMemcpyDeviceToHost); 
} 
 
// Check if there is a device supporting CUDA 
bool CheckDevice() 
{ 
#if __DEVICE_EMULATION__ 
    return true; 
#else 
    int deviceCount; 
    cudaGetDeviceCount(&deviceCount); 
    if (deviceCount == 0) 
        return false; 
    int dev; 
    for (dev = 0; dev < deviceCount; ++dev) { 
        cudaDeviceProp deviceProp; 
        cudaGetDeviceProperties(&deviceProp, dev); 
        if (strncmp(deviceProp.name, "Device Emulation", 16)) 
            break; 
    } 
    if (dev == deviceCount) 
        return false; 
    else { 
        cudaSetDevice(dev); 
        return true; 
    } 
#endif 
} 
 
// Compute L2-norm error 
double ComputeL2NormError(const Vector V, const VectorD Vref){ 
    double error = 0; 
    double ref = 0; 
    for (int i = 0; i < V.length; ++i) { 
        double diff = V.e[i] - Vref.e[i]; 
        error += diff * diff; 
        ref += Vref.e[i] * Vref.e[i]; 
    } 
    double normRef = sqrt(ref); 
    if (fabs(ref) < 1e-15) { 
        printf("ComputeL2NormError(): Reference L2-norm is zero.\n"); 
        return -1; 
    } 
    double normError = sqrt(error); 
    return normError / normRef; 
} 
 

