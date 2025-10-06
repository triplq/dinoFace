#include <iostream>
#include <onnxruntime/onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace std;
using namespace cv;
using namespace Ort;

vector<string> class_names{"close", "open"};

Env env(ORT_LOGGING_LEVEL_WARNING, "YOLOv8");
SessionOptions session_options;
Session session(env, "./Resources/best.onnx", session_options);

struct Letterbox{
    Mat img; int dh; int dw; float r;
};

Letterbox letterboxing(const Mat& orig, const int& size = 640){
    int h = orig.rows;
    int w = orig.cols;

    float r = min((float)size / (float)h, (float)size / (float)w);
    int pad_h = round(h * r);
    int pad_w = round(w * r);

    Mat new_img;
    int dh = (size - pad_h);
    int dw = (size - pad_w);

    dh /= 2; dw /= 2;

    resize(orig, new_img, Size(pad_w, pad_h));
    copyMakeBorder(new_img, new_img, dh, dh, dw, dw, BORDER_CONSTANT, Scalar(114, 114, 114));

    return {new_img, dh, dw, r};
}

Rect deletterbox(const Point& p1, const Point& p2, const Letterbox& lb){
    int x1 = round((p1.x - lb.dw) / lb.r);
    int y1 = round((p1.y - lb.dh) / lb.r);
    int x2 = round((p2.x - lb.dw) / lb.r);
    int y2 = round((p2.y - lb.dh) / lb.r);

    return {Point(x1,y1), Point(x2,y2)};
}

void parse_model(std::vector<Ort::Value>& output, const Letterbox& lb, Mat& img){
    auto output_shape = output[0].GetTensorTypeAndShapeInfo().GetShape();
    auto output_data_ptr = output[0].GetTensorData<float>();

    vector<float> output_data(output_data_ptr, output_data_ptr + output_shape[0] * output_shape[1] * output_shape[2]);

    vector<Rect> bboxes;
    vector<float> scores;
    vector<string> classes;

    for(size_t i = 0; i < output_shape[2]; i++){
        int xc = static_cast<int>(output_data[i]);
        int yc = static_cast<int>(output_data[i + output_shape[2]]); 
        int w = static_cast<int>(output_data[i + output_shape[2] * 2]);
        int h = static_cast<int>(output_data[i + output_shape[2] * 3]);
        float score0 = output_data[i + output_shape[2] * 4];
        float score1 = output_data[i + output_shape[2] * 5];

        Rect bbox = deletterbox(Point(xc - w/2, yc - h/2), Point(xc + w/2, yc + h/2), lb);

        if(score0 > score1 && score0 > 0.4f){
            bboxes.push_back(bbox);
            scores.push_back(score0);
            classes.push_back(class_names[0]);
        }

        else if(score0 < score1 && score1 > 0.4f){
            bboxes.push_back(bbox);
            scores.push_back(score1);
            classes.push_back(class_names[1]);
        }
    }

    vector<int> indicies;
    dnn::NMSBoxes(bboxes, scores, 0.30f, 0.45f, indicies);

    for(auto idx : indicies){
        auto color = CV_RGB(0,0,0);

        if(classes[idx] == "open")
            color = CV_RGB(255,0,255);
        else
            color = CV_RGB(0,255,0);

        std::string name = classes[idx] + ": " + std::to_string(static_cast<int>(scores[idx] * 100)) + "%";

        rectangle(img, bboxes[idx], color, 2);
        putText(img, name, Point(bboxes[idx].x, bboxes[idx].y), FONT_HERSHEY_COMPLEX_SMALL, 1, color);
    }
}

std::vector<Ort::Value> inferensing(const Letterbox& lb){
    vector<int64_t> shape = {1, lb.img.channels(), lb.img.rows, lb.img.cols};
    Mat nchw = dnn::blobFromImage(lb.img, 1.0/255.0, {}, {}, true);
    vector<float> input_data(nchw.begin<float>(), nchw.end<float>());

    auto memory_info = MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    auto value = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_data.size(), shape.data(), shape.size());

    const char* input_names[] = {"images"};
    const char* output_names[] = {"output0"};

    std::vector<Ort::Value> output = session.Run({}, input_names, &value, 1, output_names, 1);

    return output;
}

void work(Mat& img){
    Letterbox lb;
    lb = letterboxing(img);
    auto output = inferensing(lb);
    parse_model(output, lb, img);
}

int main(){
    VideoCapture cap(0);
    Mat frame;

    while(true){
        cap >> frame;
        work(frame);
        imshow("vid", frame);
        if(waitKey(30) == 'q')
            break;
    }
    return 0;
}
