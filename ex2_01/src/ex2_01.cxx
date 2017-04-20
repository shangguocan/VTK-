#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

int main()
{
  // ����һ��Բ׶����������������߶ȡ�����뾶�ͷֱ��ʡ�
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );
  cone->SetRadius( 1.0 );
  cone->SetResolution( 10 );
  
  // ����һ�������ӳ���������ڰѶ��������ӳ��Ϊ�ɱ��������Ⱦ��ͼԪ��
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  // ����һ����Ա��������һ��ӳ�������Ӷ�ȷ������Ա����״��
  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper( coneMapper );

  // ����һ����Ⱦ�������Ҫ����Ⱦ����Ա�����ñ�����ɫ��
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );

  // ������Ⱦ���ڣ�����Ⱦ����Ⱦ�á�
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 300, 300 );

  // ��Ⱦ360�Σ�������Ҫ��Ϊ����ʱ��
  int i;
  for (i = 0; i < 3600; ++i)  renWin->Render();
  
  // �������
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  ren1->Delete();
  renWin->Delete();

  return 0;
}
