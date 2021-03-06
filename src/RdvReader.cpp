/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlane.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include "RdvReader.h"

bool RdvReader::Read(string path, vtkPolyData *polyData)
{
    ifstream in(path, ifstream::binary);
    if (!in)
    {
        cout << "File not found:" << path << endl;
        return false;
    }

    char s[1000];
    in.getline(s, 1000);
    in.getline(s, 1000);
    in.getline(s, 1000);


    vtkPoints* points = vtkPoints::New();
    vtkDoubleArray* values = vtkDoubleArray::New();
    while(in.getline(s, 1000))
    {
        char time[20];
        sscanf(s, "%s", time);

        float f, x, y, z, v;
        sscanf(s, "%s%f%f%f%f%f%f", time, &f, &f, &x, &y, &z, &v);

        points->InsertNextPoint(x, y, z);

        printf("%f,%f,%f", x, y, z);
        values->InsertNextTuple1(v);
    }

    polyData->SetPoints(points);
    polyData->GetPointData()->SetScalars(values);

    points->Delete();
    values->Delete();

    return true;
}
