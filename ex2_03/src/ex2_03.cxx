#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCommand.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

// 交互时被回调。
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New() 
    { return new vtkMyCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkRenderer *renderer = reinterpret_cast<vtkRenderer*>(caller);
      cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
           << renderer->GetActiveCamera()->GetPosition()[1] << " "
           << renderer->GetActiveCamera()->GetPosition()[2] << "\n";
    }
};

int main()
{
  //
  // 与上例的流水线一样。
  //
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );
  cone->SetRadius( 1.0 );
  cone->SetResolution( 10 );

  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );
  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper( coneMapper );

  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );
  ren1->ResetCamera();

  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 300, 300 );

  // 添加一个观察员。
  vtkMyCallback *mo1 = vtkMyCallback::New();
  ren1->AddObserver(vtkCommand::StartEvent,mo1);
  mo1->Delete();
  
  int i;
  for (i = 0; i < 360; ++i)
    {
    renWin->Render();
    ren1->GetActiveCamera()->Azimuth( 1 );
    }

  return 0;
}
