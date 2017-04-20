#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

int main()
{
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );
  cone->SetRadius( 1.0 );
  cone->SetResolution( 10 );
  
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper( coneMapper );

  //
  // 创建两个渲染器，并分别分配演员、设置视口背景颜色以及尺寸。
  //
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );
  ren1->SetViewport(0.0, 0.0, 0.5, 1.0);

  vtkRenderer *ren2= vtkRenderer::New();
  ren2->AddActor( coneActor );
  ren2->SetBackground( 0.2, 0.3, 0.5 );
  ren2->SetViewport(0.5, 0.0, 1.0, 1.0);

  // 创建渲染窗口，添加两个渲染器。窗口的宽度是前例的两倍。
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->AddRenderer( ren2 );
  renWin->SetSize( 600, 300 );

  // 将一个圆锥旋转90°，以区别另一个。
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(90);

  int i;
  for (i = 0; i < 360; ++i)
    {
    renWin->Render();
    ren1->GetActiveCamera()->Azimuth( 1 );
    ren2->GetActiveCamera()->Azimuth( 1 );
    } 

  return 0;
}