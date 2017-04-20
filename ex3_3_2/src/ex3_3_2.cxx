// 《医学图像编程技术》 Page81-85 3.3各种数据类型 3.3.2 结构化点数据集

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
  
  // 创建结构化点数据集。
  vtkStructuredPoints *vol = vtkStructuredPoints::New();
      vol->SetDimensions(26,26,26);
	  vol->SetOrigin(-0.5,-0.5,-0.5);
	  sp = 1.0/25.0;
	  vol->SetSpacing(sp, sp, sp);					// 设置间隔

  // 创建标量数据。
  vtkFloatArray *scalars = vtkFloatArray::New();
    scalars->SetNumberOfTuples(26*26*26);		// 设置标量个数
  
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
	       s = x*x + y*y + z*z -(0.4*0.4);				// 计算标量值
        offset = i + jOffset + kOffset;				// 计算id
        scalars->InsertTuple1(offset,s);				// 插入标量值
        }
      }
    }
  vol->GetPointData()->SetScalars(scalars);			// 将标量值与点关联
  scalars->Delete();

  // 抽取标量值为0的点所形成的面。
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
