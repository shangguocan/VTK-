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
  // ����������Ⱦ�������ֱ������Ա�������ӿڱ�����ɫ�Լ��ߴ硣
  //
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );
  ren1->SetViewport(0.0, 0.0, 0.5, 1.0);

  vtkRenderer *ren2= vtkRenderer::New();
  ren2->AddActor( coneActor );
  ren2->SetBackground( 0.2, 0.3, 0.5 );
  ren2->SetViewport(0.5, 0.0, 1.0, 1.0);

  // ������Ⱦ���ڣ����������Ⱦ�������ڵĿ����ǰ����������
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->AddRenderer( ren2 );
  renWin->SetSize( 600, 300 );

  // ��һ��Բ׶��ת90�㣬��������һ����
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