// ��ҽѧͼ���̼����� Page81-85 3.3������������ 3.3.2 �ṹ�������ݼ�

#include "vtkActor.h"
#include "vtkFloatArray.h"
#include "vtkContourFilter.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStructuredPoints.h"

int main()
{
  int i, j, k, kOffset, jOffset, offset;
  float s, sp, x, y, z;
  
  // �����ṹ�������ݼ���
  vtkStructuredPoints *vol = vtkStructuredPoints::New();
      vol->SetDimensions(26,26,26);
	  vol->SetOrigin(-0.5,-0.5,-0.5);
	  sp = 1.0/25.0;
	  vol->SetSpacing(sp, sp, sp);					// ���ü��

  // �����������ݡ�
  vtkFloatArray *scalars = vtkFloatArray::New();
    scalars->SetNumberOfTuples(26*26*26);		// ���ñ�������
  
  for ( k=0; k<26; k++)
    {
    z = -0.5 + k*sp;
    kOffset = k * 26 * 26;
    for (j=0; j<26; j++) 
      {
      y = -0.5 + j*sp;
      jOffset = j * 26;
      for (i=0; i<26; i++) 
        {
        x = -0.5 + i * sp;
	       s = x*x + y*y + z*z -(0.4*0.4);				// �������ֵ
        offset = i + jOffset + kOffset;				// ����id
        scalars->InsertTuple1(offset,s);				// �������ֵ
        }
      }
    }
  vol->GetPointData()->SetScalars(scalars);			// ������ֵ������
  scalars->Delete();

  // ��ȡ����ֵΪ0�ĵ����γɵ��档
  vtkContourFilter *contour = vtkContourFilter::New();
      contour->SetInputData(vol);
      contour->SetValue(0, 0);

  vtkPolyDataMapper *volMapper = vtkPolyDataMapper::New();
      volMapper->SetInputConnection(contour->GetOutputPort());
  vtkActor *volActor = vtkActor::New();
      volActor->SetMapper(volMapper);
      volActor->GetProperty()->SetRepresentationToWireframe();
      volActor->GetProperty()->SetColor(0,0,0);

  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
    renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWin);

  renderer->AddActor(volActor);
  renderer->SetBackground(1,1,1);
  renderer->ResetCamera();

  renWin->SetSize(300,300);

  renWin->Render();
  iren->Start();

  return 0;
}
