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
// ����
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
  //����3D���ڲ���ӵ���
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  //�����Ӵ����󲢸�����������һ�����ơ�3D viewer������������Ϊshared_ptr���ܹ���ָ�룬�������Ա�֤��ָ������������ȫ��ʹ�ã����������ڴ����
  //ͨ��������û�����Ҫ��ô��
  viewer->setBackgroundColor (0, 0, 0);
  //�Ӵ��ı���ɫ������Ϊ�û�ϲ��������RGB��ɫ�������н�������Ϊ��ɫ��
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
  //��������Ҫ��һ�У����ǽ�������ӵ��Ӵ������в�����һ��Ψһ���ַ�����ΪID��
  //���ô��ַ�����֤��������Ա������Ҳ�ܱ�־���øõ��ƣ���ε���addPointCloud��������ʵ�ֶ�����Ƶ����
  //ÿ����һ�ξʹ���һ���µ�ID�ţ���������һ���Ѿ���ʾ�ĵ��ƣ��û������ȵ���removePointCloud���������ṩ��Ҫ���µĵ��Ƶ�ID�š�
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
  //�ı���ʾ���Ƶĳߴ磬�û��������ø÷������Ƶ������Ӵ��е���ʾ��ʽ��
  viewer->addCoordinateSystem (1.0);
  //��ʾ����ϵͳ����X����ɫ��Y����ɫ��Z����ɫ��Բ����������������ʾ��ʽ
  //Բ����Ĵ�Сͨ��scale�������ƣ���������Ϊ1.0����ֵҲΪĬ��ֵ��
  //�÷�������һ���غ�����ʵ�ֶԵ����е�ÿ��������귽�������ʾ��
  viewer->initCameraParameters ();
  //�������������ʹ�û���Ĭ�ϵĽǶȺͷ���۲���ơ�
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> rgbVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{//����ʹ�õĵ��ƴ���RGN���ݵ������ֶ�
  //����3D���ڲ���ӵ���	
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  //���ô��ڵı�����ɫ
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  //����һ����ɫ�������PointCloudColorHandlerRGB��PCLVisualizer�����������Ķ�����ʾ�Զ�����ɫ����
  //�����ʾ���У�PointCloudColorHandlerRGB����õ�ÿ�����Ƶ�RGV��ɫ�ֶ�
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  //ָ����ӵ��Ӵ��е��Ƶ�PointCloudColorHandlerRGB��ɫ�������
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> customColourVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
//����3D���ڲ���ӵ���
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
  //����һ���Զ�����ɫ������PointCloudColorHandlerCustom���󣬲�������ɫΪ����ɫ
  viewer->addPointCloud<pcl::PointXYZ> (cloud, single_color, "sample cloud");
  //����addPointCloud��ɶ���ɫ����������Ĵ���
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> normalsVis (
    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::ConstPtr normals)
{
  //����3D���ڲ���ӵ������������  
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals, 10, 0.05, "normals");
  //��ʾ���Ʒ���
  //�����з�����ʾ�ĸ��������ÿ10������ʾһ������ÿ�����ߵĳ��ȣ�0.05��
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}


boost::shared_ptr<pcl::visualization::PCLVisualizer> shapesVis (pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{
    //���������״��
    //�Ե����е�һ���㵽���һ����֮������ߡ�ԭ������ƽ�桢
    //�Ե����е�һ����Ϊ���ĵ����塢��y���׶��
   //����3D���ڲ���ӵ���    
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  //�ڵ��������ֱ�ߺ�����ģ��
  viewer->addLine<pcl::PointXYZRGB> (cloud->points[0],
                                     cloud->points[cloud->size() - 1], "line");
  //����Ĭ����ɫ��Ҳ���Զ�����ɫ
  viewer->addSphere (cloud->points[0], 0.2, 0.5, 0.5, 0.0, "sphere");
  //����Ե����е�һ����Ϊ���ġ��뾶Ϊ0.2�����壬ͬʱҲ��Ϊ�������Զ�����ɫ
  
  //������λ����ӻ���ģ�Ͳ�����ƽ�漰Բ׶��
   pcl::ModelCoefficients coeffs;
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (1.0);
  coeffs.values.push_back (0.0);
  viewer->addPlane (coeffs, "plane");
  //����ƽ�棬�ñ�׼��ƽ�淽��(ax+by+cz+d=0)������ƽ��
  //���ƽ����ԭ��Ϊ���ģ�������z����
  coeffs.values.clear ();
  coeffs.values.push_back (0.3);
  coeffs.values.push_back (0.3);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (1.0);
  coeffs.values.push_back (0.0);
  coeffs.values.push_back (5.0);
  viewer->addCone (coeffs, "cone");
  //���׶�Σ�����ģ�Ͳ���ָ��׶�εĲ���

  return (viewer);
}


boost::shared_ptr<pcl::visualization::PCLVisualizer> viewportsVis (
    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud, pcl::PointCloud<pcl::Normal>::ConstPtr normals1, pcl::PointCloud<pcl::Normal>::ConstPtr normals2)
{
  // ����3D���ڲ������ʾ�������������
   boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->initCameraParameters ();
  //�����Ӵ�����
  int v1(0);
  viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
  //�����µ��ӿڣ������4���������ӿ���X�����Сֵ�����ֵ��Y�����Сֵ�����ֵ��ȡֵ��0~1.
  //�������ӿڷֲ��ڴ��ڵ���벿��
  //���һ���ַ�������������Ψһ��־���ӿڣ��������ı���ӿ����ݵĵ�������Ҫ�Ը�Ψһ��־Ϊ����
  viewer->setBackgroundColor (0, 0, 0, v1);
  //�����ӿڵı�����ɫ�����һ����ǩ�������������ӿ�
  viewer->addText("Radius: 0.01", 10, 10, "v1 text", v1);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, rgb, "sample cloud1", v1);
  //����rgb��ɫ��ɫ������ӵ��Ƶ���ǰ�ӿ���
  int v2(0);
  viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
  //�Ұ봰��
  viewer->setBackgroundColor (0.3, 0.3, 0.3, v2);
  //�ӿڱ��������ɫ
  viewer->addText("Radius: 0.1", 10, 10, "v2 text", v2);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> single_color(cloud, 0, 255, 0);
  viewer->addPointCloud<pcl::PointXYZRGB> (cloud, single_color, "sample cloud2", v2);
  //���������Զ�����ɫ��ɫ
  
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
  viewer->addCoordinateSystem (1.0);
  //Ϊ�����ӿ��������ԣ������PCLVsiaulizer��ķ�����Ա����һ������ѡ����ӿ�ID������
  //�����øò���ʱ���÷���ֻ�������������ӿڣ������øò����Ļ��÷��������������ӿڡ�
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals1, 10, 0.05, "normals1", v1);
  viewer->addPointCloudNormals<pcl::PointXYZRGB, pcl::Normal> (cloud, normals2, 10, 0.05, "normals2", v2);
  //��ӷ��ߣ�ÿ���ӿڶ���һ���Ӧ�ķ���
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
  //���Ǽ�鰴�µ��Ǹ����������r������ɾ��ǰ��������������ı���ǩ
  //��Ҫע�⣬������r��ʱ��3D������Ի����ã����ԣ���PCL���Ӵ�ע����¼���Ӧ�ص����������Ḳ��������Ա��ͬһ�¼�����Ӧ��
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
  //��������¼��ĺ�����ÿ����Ӧ����¼�ʱ����ص��ú�����
  //Ϊ����Ӧ���ǹ��ĵ��¼�����Ҫ��eventʵ����ȡ�¼���Ϣ���ڱ����в������������ͷ��¼���ÿ����Ӧ�����¼�ʱ��������갴�µ�λ��������һ��С���ı���ǩ
  
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> interactionCustomizationVis ()
{
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addCoordinateSystem (1.0);

  viewer->registerKeyboardCallback (keyboardEventOccurred, (void*)&viewer);
  viewer->registerMouseCallback (mouseEventOccurred, (void*)&viewer);
  //�ֱ�ע����Ӧ���̺�����¼���keyboardEventOccurred��mouseEventOccurred�ص�������
  //�ڶ�����������ν��cookies���ǻص�ʱ���ݸ��ص������Ĳ���
  //���Դ�������������ص��������ڱ��������Ӵ�������Ϊ�������ݸ��ص�������Ŀ�������û�����ʱ�����ûص�������Ҫ�ı��Ӵ���������ݣ�
  //��Ҫע�������Щ���������õ���void*����ʽ��������Ҫ��ָ��boost::shared_ptrǿ��ת��Ϊvoid*��
  return (viewer);
}
// -----Main-----
int
main (int argc, char** argv)
{
  // ���������в���
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
  // ���д���һ�������
  pcl::PointCloud<pcl::PointXYZ>::Ptr basic_cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr (new pcl::PointCloud<pcl::PointXYZRGB>);
  std::cout << "Genarating example point clouds.\n\n";
  // ����ԲΪ������z�������ȡ����ƣ����������������ɫ��
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
  // 0.05Ϊ�����뾶��ȡ���Ʒ���
  pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;
  ne.setInputCloud (point_cloud_ptr);
  pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB> ());
  ne.setSearchMethod (tree);
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals1 (new pcl::PointCloud<pcl::Normal>);
  ne.setRadiusSearch (0.05);
  ne.compute (*cloud_normals1);
  //  0.1Ϊ�����뾶��ȡ���Ʒ���
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
  // ��ѭ��
  while (!viewer->wasStopped ())
  {
    viewer->spinOnce (100);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    //boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  }
  //ÿ�ε���spinOnce���������Ӵ������¼���ʱ�䣬�������������̵Ƚ�������
  //���⻹��һ��SPIN�����ط�������ֻ�����һ��
}
