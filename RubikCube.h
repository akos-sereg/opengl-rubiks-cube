
struct info
{
	char *line;
} info[] = {
	{"q,w,e,r,t,z,u,i,o,p,a,s,d,f,g,h,j,k: Rotate commands"},
	{"m: Rotate randomly"},
	{"2: Solve Cube (animated)"},
	{"3: Load Cube"},
	{"6,7,8,9: Speed - slower->faster"},
	{"F3: Move towards"},
	{"F4: Move backwards"},
	{"Up, down, left, right: Change moving direction"},
	{"Space: Stop"},
	{""}
};

/*#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace RubikCube
{
	/// <summary> 
	/// Summary for RubikCube
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class RubikCube : public System::Windows::Forms::Form
	{
	public: 
		RubikCube(void)
		{
			InitializeComponent();
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
        
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = S"RubikCube";
		}		
	};
}*/