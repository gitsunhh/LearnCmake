/* \author Geoffrey Biggs */
#include <thread>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
// 帮助
void
printUsage (const char* progName)
{
  std::cout << "\n\nUsage: "<<progName<<" [options]\n\n"
            << "Options:\n"
            << "-------------------------------------------\n"
            << "-h           this help\n"
            << "-s           Simple visualisation example\n"
            << "-r           RGB colour visualisation example\n"
            << "-c           Custom colour visualisation example\n"
            << "-n           Normals visualisation example\n"
            << "-a           Shapes visualisation example\n"
            << "-v           Viewports example\n"
            << "-i           Interaction Customization example\n"
            << "\n\n";
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
  //创建3D窗口并添加点云
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  //创建视窗对象并给标题栏定义一个名称“3D viewer”，将它定义为shared_ptr智能共享指针，这样可以保证该指针在整个程序全局使用，而不引起内存错误
  //通常情况下用户不需要这么做
  viewer->setBackgroundColor (0, 0, 0);
  //视窗的背景色可以设为用户喜欢的任意RGB颜色，本例中将它设置为黑色。
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
  //这是最重要的一行，我们将点云添加到视窗对象中并定义一个唯一的字符串作为ID号
  //利用此字符串保证在其他成员方法中也能标志引用该点云，多次调用addPointCloud（）可以实现多个点云的添加
  //每调用一次就创建一个新的ID号，如果想更新一个已经显示的点云，用户必须先调用removePointCloud（），并提供需要更新的点云的ID号。
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
  //改变显示点云的尺寸，用户可以利用该方法控制点云在视窗中的显示方式。
  viewer->addCoordinateSystem (1.0);
  //显示坐标系统方向，X（红色）Y（绿色）Z（蓝色）圆柱体代表坐标轴的显示方式
  //圆柱体的大小通过scale参数控制，本例中设为1.0，该值也为默认值。
  //该方法的另一重载函数可实现对点云中的每个点的坐标方向进行显示。
  viewer->initCameraParameters ();
  //设置照相机参数使用户从默认的角度和方向观察点云。
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> rgbVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{//这里使用的点云带有RGN数据的属性字段
  //创建3D窗口并添加点云	
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  //设置窗口的背景颜色
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  //创建一个颜色处理对象PointCloudColorHandlerRGB，PCLVisualizer类利用这样的对象显示自定义颜色数据
  //在这个示例中，PointCloudColorHandlerRGB对象得到每个点云的RGV颜色字段
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  //指定添加到视窗中点云的PointCloudColorHandlerRGB着色处理对象。
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> customColourVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
//创建3D窗口并添加点云
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
  //创建一个自定义颜色处理器PointCloudColorHandlerCustom对象，并设置颜色为纯绿色
  viewer->addPointCloud<pcl::PointXYZ> (cloud, single_color, "sample cloud");
  //调用addPointCloud完成对颜色处理器对象的传递
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> normalsVis (
    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::ConstPtr normals)
{
  //创建3D窗口并添加点云其包括法线  
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals, 10, 0.05, "normals");
  //显示点云法线
  //参数有法线显示的个数（这里，每10个点显示一个）及每个法线的长度（0.05）
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}


boost::shared_ptr<pcl::visualization::PCLVisualizer> shapesVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{
    //添加四种形状：
    //以点云中第一个点到最后一个点之间的连线、原点所在平面、
    //以点云中第一个点为中心的球体、沿y轴的锥体
   //创建3D窗口并添加点云    
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  //在点云上添加直线和球体模型
  viewer->addLine<pcl::PointXYZRGB> (cloud->points[0],
                                     cloud->points[cloud->size() - 1], "line");
  //线用默认颜色，也可自定义颜色
  viewer->addSphere (cloud->points[0], 0.2, 0.5, 0.5, 0.0, "sphere");
  //添加以点云中第一个点为中心、半径为0.2的球体，同时也可为该球体自定义颜色
  
  //在其他位置添加基于模型参数的平面及圆锥体
   pcl::ModelCoefficients coeffs;
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (1.0);
  coeffs.values.push_back (0.0);
  viewer->addPlane (coeffs, "plane");
  //绘制平面，用标准的平面方程(ax+by+cz+d=0)来定义平面
  //这个平面以原点为中心，方向沿z方向
  coeffs.values.clear ();
  coeffs.values.push_back (0.3);
  coeffs.values.push_back (0.3);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (1.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (5.0);
  viewer->addCone (coeffs, "cone");
  //添加锥形，利用模型参数指定锥形的参数

  return (viewer);
}


boost::shared_ptr<pcl::visualization::PCLVisualizer> viewportsVis (
    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::ConstPtr normals1, pcl::PointCloud<pcl::Normal>::ConstPtr normals2)
{
  // 创建3D窗口并添加显示点云其包括法线
   boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->initCameraParameters ();
  //创建视窗对象
  int v1(0);
  viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
  //创建新的视口，所需的4个参数是视口在X轴的最小值、最大值、Y轴的最小值、最大值，取值在0~1.
  //创建的视口分布于窗口的左半部分
  //最后一个字符串参数，用来唯一标志该视口，在其他改变该视口内容的调用中需要以该唯一标志为参数
  viewer->setBackgroundColor (0, 0, 0, v1);
  //设置视口的背景颜色，添加一个标签以区别于其他视口
  viewer->addText("Radius: 0.01", 10, 10, "v1 text", v1);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud1", v1);
  //利用rgb颜色着色器并添加点云到当前视口中
  int v2(0);
  viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
  //右半窗口
  viewer->setBackgroundColor (0.3, 0.3, 0.3, v2);
  //视口背景赋予灰色
  viewer->addText("Radius: 0.1", 10, 10, "v2 text", v2);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> single_color(cloud, 0, 255, 0);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, single_color, "sample cloud2", v2);
  //给点云用自定义颜色着色
  
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
  viewer->addCoordinateSystem (1.0);
  //为所有视口设置属性，大多数PCLVsiaulizer类的方法成员都有一个可以选择的视口ID参数，
  //当设置该参数时，该方法只作用于所设置视口，不设置该参数的话该方法作用于所有视口。
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals1, 10, 0.05, "normals1", v1);
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals2, 10, 0.05, "normals2", v2);
  //添加法线，每个视口都有一组对应的法线
  return (viewer);
}


unsigned int text_id = 0;
void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event,
                            void* viewer_void)
{
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = *static_cast<boost::shared_ptr<pcl::visualization::PCLVisualizer> *> (viewer_void);
  if (event.getKeySym () == "r" && event.keyDown ())
  {
    std::cout << "r was pressed => removing all text" << std::endl;

    char str[512];
    for (unsigned int i = 0; i < text_id; ++i)
    {
      sprintf (str, "text#%03d", i);
      viewer->removeShape (str);
    }
    text_id = 0;
  }
  //我们检查按下的那个键，如果按r键，则删除前面鼠标所产生的文本标签
  //需要注意，当按下r键时，3D照相机仍会重置，所以，在PCL中视窗注册的事件响应回调函数，不会覆盖其他成员对同一事件的响应。
}

void mouseEventOccurred (const pcl::visualization::MouseEvent &event,
                         void* viewer_void)
{
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = *static_cast<boost::shared_ptr<pcl::visualization::PCLVisualizer> *> (viewer_void);
  if (event.getButton () == pcl::visualization::MouseEvent::LeftButton &&
      event.getType () == pcl::visualization::MouseEvent::MouseButtonRelease)
  {
    std::cout << "Left mouse button released at position (" << event.getX () << ", " << event.getY () << ")" << std::endl;

    char str[512];
    sprintf (str, "text#%03d", text_id ++);
    viewer->addText ("clicked here", event.getX (), event.getY (), str);
  }
  //处理鼠标事件的函数，每次响应鼠标事件时都会回调该函数。
  //为了响应我们关心的事件，需要从event实例提取事件信息，在本例中查找鼠标左键的释放事件，每次响应这种事件时都会在鼠标按下的位置上生成一个小的文本标签
  
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> interactionCustomizationVis ()
{
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addCoordinateSystem (1.0);

  viewer->registerKeyboardCallback (keyboardEventOccurred, (void*)&viewer);
  viewer->registerMouseCallback (mouseEventOccurred, (void*)&viewer);
  //分别注册相应键盘和鼠标事件的keyboardEventOccurred和mouseEventOccurred回调函数，
  //第二个参数是所谓的cookies，是回调时传递给回调函数的参数
  //可以传递任意参数给回调函数，在本例中以视窗对象本身为参数传递给回调函数，目的是在用户交互时，调用回调函数需要改变视窗对象的内容，
  //需要注意的是这些参数必须用单个void*的形式，所以需要将指针boost::shared_ptr强制转换为void*。
  return (viewer);
}
// -----Main-----
int
main (int argc, char** argv)
{
  // 解析命令行参数
  if (pcl::console::find_argument (argc, argv, "-h") >= 0)
  {
    printUsage (argv[0]);
    return 0;
  }
  bool simple(false), rgb(false), custom_c(false), normals(false),
    shapes(false), viewports(false), interaction_customization(false);
  if (pcl::console::find_argument (argc, argv, "-s") >= 0)
  {
    simple = true;
    std::cout << "Simple visualisation example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-c") >= 0)
  {
    custom_c = true;
    std::cout << "Custom colour visualisation example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-r") >= 0)
  {
    rgb = true;
    std::cout << "RGB colour visualisation example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-n") >= 0)
  {
    normals = true;
    std::cout << "Normals visualisation example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-a") >= 0)
  {
    shapes = true;
    std::cout << "Shapes visualisation example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-v") >= 0)
  {
    viewports = true;
    std::cout << "Viewports example\n";
  }
  else if (pcl::console::find_argument (argc, argv, "-i") >= 0)
  {
    interaction_customization = true;
    std::cout << "Interaction Customization example\n";
  }
  else
  {
    printUsage (argv[0]);
    return 0;
  }
  // 自行创建一随机点云
  pcl::PointCloud<pcl::PointXYZ>::Ptr basic_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
  std::cout << "Genarating example point clouds.\n\n";
  // 以椭圆为边线沿z轴拉伸获取其点云，并赋予红绿蓝渐变色。
  uint8_t r(255), g(15), b(15);
  for (float z(-1.0); z <= 1.0; z += 0.05)
  {
    for (float angle(0.0); angle <= 360.0; angle += 5.0)
    {
      pcl::PointXYZ basic_point;
      basic_point.x = 0.5 * cosf (pcl::deg2rad(angle));
      basic_point.y = sinf (pcl::deg2rad(angle));
      basic_point.z = z;
      basic_cloud_ptr->points.push_back(basic_point);

      pcl::PointXYZRGB point;
      point.x = basic_point.x;
      point.y = basic_point.y;
      point.z = basic_point.z;
      uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
              static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
      point.rgb = *reinterpret_cast<float*>(&rgb);
      point_cloud_ptr->points.push_back (point);
    }
    if (z < 0.0)
    {
      r -= 12;
      g += 12;
    }
    else
    {
      g -= 12;
      b += 12;
    }
  }
  basic_cloud_ptr->width = (int) basic_cloud_ptr->points.size ();
  basic_cloud_ptr->height = 1;
  point_cloud_ptr->width = (int) point_cloud_ptr->points.size ();
  point_cloud_ptr->height = 1;
  // 0.05为搜索半径获取点云法线
  pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
  ne.setInputCloud (point_cloud_ptr);
  pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB> ());
  ne.setSearchMethod (tree);
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals1 (new pcl::PointCloud<pcl::Normal>);
  ne.setRadiusSearch (0.05);
  ne.compute (*cloud_normals1);
  //  0.1为搜索半径获取点云法线
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals2 (new pcl::PointCloud<pcl::Normal>);
  ne.setRadiusSearch (0.1);
  ne.compute (*cloud_normals2);

  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  if (simple)
  {
    viewer = simpleVis(basic_cloud_ptr);
  }
  else if (rgb)
  {
    viewer = rgbVis(point_cloud_ptr);
  }
  else if (custom_c)
  {
    viewer = customColourVis(basic_cloud_ptr);
  }
  else if (normals)
  {
    viewer = normalsVis(point_cloud_ptr, cloud_normals2);
  }
  else if (shapes)
  {
    viewer = shapesVis(point_cloud_ptr);
  }
  else if (viewports)
  {
    viewer = viewportsVis(point_cloud_ptr, cloud_normals1, cloud_normals2);
  }
  else if (interaction_customization)
  {
    viewer = interactionCustomizationVis();
  }
  // 主循环
  while (!viewer->wasStopped ())
  {
    viewer->spinOnce (100);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    //boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
  //每次调用spinOnce（）都给视窗处理事件的时间，这样允许鼠标键盘等交互操作
  //此外还有一种SPIN的重载方法，它只需调用一次
}
