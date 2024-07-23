

#if defined(WIN32) || defined(_WIN32)
#include <time.h>
#else
#include <unistd.h>
#endif

#include "YOLOv5sImpl.h"
#include "comm.h"
namespace yolov5 {

ObjectDetection::ObjectDetection()
{
    impl = new ObjectDetectionImpl();
}

ObjectDetection::~ObjectDetection()
{
    if (nullptr != impl) {
        delete static_cast<ObjectDetectionImpl*>(impl);
        impl = nullptr;
    }
}

bool ObjectDetection::Init(const ObjectDetectionConfig& config)
{
    if (IsInitialized()) {
        return static_cast<ObjectDetectionImpl*>(impl)->DeInitialize() &&
               static_cast<ObjectDetectionImpl*>(impl)->Initialize(config);
    } else
    {
        //走的这里
        return static_cast<ObjectDetectionImpl*>(impl)->Initialize(config);
    }

}

bool ObjectDetection::Deinit()
{
    if (nullptr != impl && IsInitialized()) {
        return static_cast<ObjectDetectionImpl*>(impl)->DeInitialize();
    } else {
        return false;
    }
}

bool ObjectDetection::IsInitialized()
{
    return static_cast<ObjectDetectionImpl*>(impl)->IsInitialized();
}

bool ObjectDetection::Detect(const cv::Mat& image, std::vector<ObjectData>& results)
{
    if (nullptr != impl && IsInitialized()) {
        //ALOGD(__func__,"============55555111111========================", "");
        auto ret = static_cast<ObjectDetectionImpl*>(impl)->Detect(image, results);
        //ALOGD(__func__,"============5555522222222========================", "");
        return ret;
    }
    else return false;
}

bool ObjectDetection::SetScoreThreshold(const float& conf_thresh, const float& nms_thresh)
{
    if (nullptr != impl) return static_cast<ObjectDetectionImpl*>(impl)->SetScoreThresh(conf_thresh, nms_thresh);
    else     return false;
}

bool ObjectDetection::SetROI(const cv::Rect& roi)
{
    if (nullptr != impl)    return static_cast<ObjectDetectionImpl*>(impl)->SetROI(roi);
    else return false;
}

bool ObjectDetection::RegisterPreProcess(pre_process_t func)
{
    if (nullptr != impl)    return static_cast<ObjectDetectionImpl*>(impl)->RegisterPreProcess(func);
    else  return false;
}

bool ObjectDetection::RegisterPreProcess(post_process_t func)
{
    if (nullptr != impl)    return static_cast<ObjectDetectionImpl*>(impl)->RegisterPreProcess(func);
    else    return false;
}

} // namespace yolov5
