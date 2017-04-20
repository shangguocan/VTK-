#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

int main()
{
  // 创建一个圆锥，并设置其参数：高度、底面半径和分辨率。
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );
  cone->SetRadius( 1.0 );
  cone->SetResolution( 10 );
  
  // 创建一个多边形映射器，用于把多边形数据映射为可被计算机渲染的图元。
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  // 创建一个演员，并关联一个映射器，从而确定了演员的形状。
  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper( coneMapper );

  // 创建一个渲染器，添加要被渲染的演员，设置背景颜色。
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );

  // 创建渲染窗口，供渲染器渲染用。
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 300, 300 );

  // 渲染360次，这里主要是为了延时。
  int i;
  for (i = 0; i < 3600; ++i)  renWin->Render();
  
  // 清除对象。
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  ren1->Delete();
  renWin->Delete();

  return 0;
}
