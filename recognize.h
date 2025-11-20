#pragma once
#ifndef MOBILEFACENET_AS_RECOGNIZE_H
#define MOBILEFACENET_AS_RECOGNIZE_H
#include <string>
#include "net.h"
#include <algorithm>

namespace Face {
    class Recognize {
    public:
        Recognize();
        void Set_model_path(const std::string &model_path);
        ~Recognize();
        void start(ncnn::Mat& ncnn_img, std::vector<float>&feature128);
        void SetThreadNum(int threadNum);                                                       //设置进程数
        void getAffineMatrix(float* src_5pts, const float* dst_5pts, float* M);                 //获取仿射矩阵
        void warpAffineMatrix(ncnn::Mat src, ncnn::Mat &dst, float *M, int dst_w, int dst_h);   //扭曲仿射矩阵，这两个矩阵应该是用来人脸对齐
        ncnn::Mat preprocess(ncnn::Mat img, int *info);                                         //预处理
    private:
        void RecogNet(ncnn::Mat& img_);
        void normalize(std::vector<float> &feature);
        ncnn::Net Recognet;
        //ncnn::Mat ncnn_img;
        std::vector<float> feature_out;
        int threadnum = 1;
    };

    double calculSimilar(std::vector<float>& v1, std::vector<float>& v2, int distance_metric);  //计算相似度
}
#endif //MOBILEFACENET_AS_RECOGNIZE_H
