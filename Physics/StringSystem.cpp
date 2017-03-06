//==========================================================
//StringSystem.cpp
//==========================================================
#include "StringSystem.hpp"

const float SQUAREROOT2 = (float)sqrt(2);
StringSystem::StringSystem()
{

}
StringSystem::StringSystem(float stringLength, float cofficient, Vector3 gravityVector, float stringCofficient, float stiffness, float mass,int row,int col)
{
	m_stringLength = stringLength;
	m_cofficient = cofficient;
	m_gravityVector = gravityVector;
	m_stringCofficient = stringCofficient;
	m_stiffness = stiffness;
	m_yoyoMass = mass;
	m_row = row;
	m_col = col;
}

void StringSystem::StartUp()
{
	Vector3 position = Vector3(0.0, 0.0f, 0.0f);
	float distanceBetween = m_stringLength;
	for (int i = 0; i < m_col*m_row;i++)
	{
		StringVerts tempVerts = StringVerts(position,m_yoyoMass);
		m_verts.push_back(tempVerts);
		position.x += distanceBetween;
		if ((i+1)%m_col == 0)
		{
			position.z-= distanceBetween;
			position.x = 0.0f;
		}
	}
}

void StringSystem::Draw(OpenGLRenderer* renderer)
{
	RGBA white(1.0f, 1.0f, 1.0f);
	for (unsigned int i = 0; i < m_verts.size(); i++)
	{
		renderer->DrawStarPoint(m_verts[i].m_position, white, 1);
		
	}
}

void StringSystem::Update(float deltaTime, OpenGLRenderer* renderer)
{
	std::vector<Vector3> forces;
	forces.clear();
	for (int i = 0; i < m_row*m_col; i++)
	{
		forces.push_back(Vector3(0.0f,0.0f,0.0f));
	}
	std::vector<Vector3> constraints;
	constraints.clear();
	for (int i = 0; i < m_row*m_col; i++)
	{
		constraints.push_back(Vector3(0.0f, 0.0f, 0.0f));
	}
	
	for (int i = 0; i < m_row - 1; i++)
	{
		for (int j = 0; j < m_col - 1; j++)
		{
			StringVerts firstVert = m_verts[i*m_col + j];
			StringVerts secondVert = m_verts[(i + 1)*m_col + j + 1];
			Vector3 prev_position = secondVert.m_position;
			Vector3 prev_velocity = secondVert.m_velocity;
	
			Vector3 next_position;
			Vector3 next_velocity;
	
			Vector3 delta_prev_position;
			Vector3 delta_prev_velocity;
	
			Vector3 next_positionF;
			Vector3 next_velocityF;
			Vector3 prev_positionF = firstVert.m_position;
			Vector3 prev_velocityF = firstVert.m_velocity;
			Vector3 delta_prev_positionF;
			Vector3 delta_prev_velocityF;
	
			delta_prev_position = prev_velocity;
			delta_prev_positionF = prev_velocityF;
	
			delta_prev_velocity.x = 0.0f;
			delta_prev_velocity.y = 0.0f;
			Vector3 e = (secondVert.m_position - firstVert.m_position);
			e.Normalize();
			Vector3 Fk = -m_stiffness*((secondVert.m_position - firstVert.m_position).CalcLength() - m_stringLength*SQUAREROOT2) * e;
			Vector3 Fc = -m_cofficient * (DotProduct(e, (secondVert.m_velocity - firstVert.m_velocity))) *e;
			Vector3 A = Fk + Fc;// -secondVert.m_mass*m_gravityVector - m_stringCofficient*secondVert.m_velocity;

			Vector3 eF = (firstVert.m_position - secondVert.m_position);
			eF.Normalize();
			Vector3 FkF = -1 * Fk;// m_stiffness*((firstVert.m_position - secondVert.m_position).CalcLength() - m_stringLength*SQUAREROOT2) * eF;
			Vector3 FcF = -1 * Fc;// m_cofficient * (DotProduct(eF, (firstVert.m_velocity - secondVert.m_velocity))) *eF;
			Vector3 AF = FkF + FcF;// -firstVert.m_mass*m_gravityVector - m_stringCofficient*firstVert.m_velocity;
		
			if (secondVert.m_isPinned == false)
			{
				forces[(i + 1)*m_col + j + 1] += A;
			}
	
			if (firstVert.m_isPinned == false)
			{
				forces[i*m_col + j] += AF;
			}
			renderer->DrawLineSegment(firstVert.m_position, secondVert.m_position, RGBA(1.0F, 0.0F, .0F), 1);
		}
		
	}
	//BOTTOM LEFT TO TOP RIGHT
	for (int i = m_row - 1; i > 0; i--)
	{
		for (int j = 0; j < m_col - 1; j++)
		{
			StringVerts firstVert = m_verts[i*m_col + j];
			StringVerts secondVert = m_verts[(i - 1)*m_col + j + 1];
			Vector3 prev_position = secondVert.m_position;
			Vector3 prev_velocity = secondVert.m_velocity;
	
			Vector3 next_position;
			Vector3 next_velocity;
	
			Vector3 delta_prev_position;
			Vector3 delta_prev_velocity;
	
			Vector3 next_positionF;
			Vector3 next_velocityF;
			Vector3 prev_positionF = firstVert.m_position;
			Vector3 prev_velocityF = firstVert.m_velocity;
			Vector3 delta_prev_positionF;
			Vector3 delta_prev_velocityF;
	
			delta_prev_position = prev_velocity;
			delta_prev_positionF = prev_velocityF;
	
			delta_prev_velocity.x = 0.0f;
			delta_prev_velocity.y = 0.0f;
			Vector3 e = (secondVert.m_position - firstVert.m_position);
			e.Normalize();
			Vector3 Fk = -m_stiffness*((secondVert.m_position - firstVert.m_position).CalcLength() - m_stringLength*SQUAREROOT2) * e;
			Vector3 Fc = -m_cofficient * (DotProduct(e, (secondVert.m_velocity - firstVert.m_velocity))) *e;
			Vector3 A = Fk + Fc;// -secondVert.m_mass*m_gravityVector - m_stringCofficient*secondVert.m_velocity;
	
			Vector3 eF = (firstVert.m_position - secondVert.m_position);
			eF.Normalize();
			Vector3 FkF = -1 * Fk;// m_stiffness*((firstVert.m_position - secondVert.m_position).CalcLength() - m_stringLength*SQUAREROOT2) * eF;
			Vector3 FcF = -1 * Fc;// m_cofficient * (DotProduct(eF, (firstVert.m_velocity - secondVert.m_velocity))) *eF;
			Vector3 AF = FkF + FcF;// -firstVert.m_mass*m_gravityVector - m_stringCofficient*firstVert.m_velocity;
			//Vector3 AF = -1 * A;
			//delta_prev_velocity.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocity = A*deltaTime;
	
			next_position = prev_position + delta_prev_position;
			next_velocity = prev_velocity + delta_prev_velocity;
			if (secondVert.m_isPinned == false)
			{
				forces[(i - 1)*m_col + j + 1] += A;
				//m_verts[(i - 1)*m_col + j + 1].m_position = next_position;
				//m_verts[(i - 1)*m_col + j + 1].m_velocity = next_velocity;
			}
	
	
			//delta_prev_velocityF.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocityF = AF*deltaTime;
			next_positionF = prev_positionF + delta_prev_positionF;
			next_velocityF = prev_velocityF + delta_prev_velocityF;
			if (firstVert.m_isPinned == false)
			{
				forces[i*m_col + j] += AF;
				//m_verts[i*m_col + j].m_position = next_positionF;
				//m_verts[i*m_col + j].m_velocity = next_velocityF;
			}
			renderer->DrawLineSegment(firstVert.m_position, secondVert.m_position, RGBA(1.0F, 0.0F, .0F), 1);
		}
	}
	//left to right
	for (int j = 0; j < m_col; j++)
	{
		for (int i = 0; i < m_row-1; i++)
		{
			StringVerts firstVert = m_verts[j*m_row+i];
			StringVerts secondVert = m_verts[j*m_row+i + 1];
			
			Vector3 prev_position = secondVert.m_position;
			Vector3 prev_velocity = secondVert.m_velocity;
			Vector3 next_position;
			Vector3 next_velocity;
			Vector3 delta_prev_position;
			Vector3 delta_prev_velocity;
	
			Vector3 next_positionF;
			Vector3 next_velocityF;
			Vector3 prev_positionF = firstVert.m_position;
			Vector3 prev_velocityF = firstVert.m_velocity;
			Vector3 delta_prev_positionF;
			Vector3 delta_prev_velocityF;
			
	
			delta_prev_position = prev_velocity;
			delta_prev_positionF = prev_velocityF;
	
			delta_prev_velocity.x = 0.0f;
			delta_prev_velocity.y = 0.0f;
			Vector3 e = (secondVert.m_position - firstVert.m_position);
			e.Normalize();
			Vector3 Fk = -m_stiffness*((secondVert.m_position - firstVert.m_position).CalcLength() - m_stringLength) * e;
			Vector3 Fc = -m_cofficient * (DotProduct(e, (secondVert.m_velocity - firstVert.m_velocity))) *e;
			Vector3 A = Fk + Fc;//  -secondVert.m_mass*m_gravityVector - m_stringCofficient*secondVert.m_velocity;
	
			Vector3 eF = (firstVert.m_position - secondVert.m_position);
			eF.Normalize();
			Vector3 FkF = -1*Fk;// m_stiffness*((firstVert.m_position - secondVert.m_position).CalcLength() - m_stringLength) * eF;
			Vector3 FcF = -1*Fc;// m_cofficient * (DotProduct(eF, (firstVert.m_velocity - secondVert.m_velocity))) *eF;
			Vector3 AF = FkF + FcF;// -firstVert.m_mass*m_gravityVector - m_stringCofficient*firstVert.m_velocity;
	
			//delta_prev_velocity.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocity = A*deltaTime;
	
			next_position = prev_position + delta_prev_position;
			next_velocity = prev_velocity + delta_prev_velocity;
	
			if (secondVert.m_isPinned==false)
			{
				forces[j*m_row + i + 1] += A;
				//m_verts[j*m_row + i + 1].m_position = next_position;
				//m_verts[j*m_row + i + 1].m_velocity = next_velocity;
			}
			
	
			delta_prev_velocityF.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocityF = AF*deltaTime;
			next_positionF = prev_positionF + delta_prev_positionF;
			next_velocityF = prev_velocityF + delta_prev_velocityF;
			if (firstVert.m_isPinned==false)
			{
				forces[j*m_row + i] += AF;
				//m_verts[j*m_row + i].m_position = next_positionF;
				//m_verts[j*m_row + i].m_velocity = next_velocityF;
			}
			
	
			renderer->DrawLineSegment(firstVert.m_position, secondVert.m_position, RGBA(1.0F, 0.0F, 1.0F), 1);
		}
	}
	
	//top to bottom
	for (int i = 0; i < m_row-1; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			StringVerts firstVert = m_verts[i*m_col +j];
			StringVerts secondVert = m_verts[(i+1)*m_col+j];
			
			Vector3 prev_position = secondVert.m_position;
			Vector3 prev_velocity = secondVert.m_velocity;
	
			Vector3 next_position;
			Vector3 next_velocity;
	
			Vector3 delta_prev_position;
			Vector3 delta_prev_velocity;
	
			Vector3 next_positionF;
			Vector3 next_velocityF;
			Vector3 prev_positionF = firstVert.m_position;
			Vector3 prev_velocityF = firstVert.m_velocity;
			Vector3 delta_prev_positionF;
			Vector3 delta_prev_velocityF;
	
			delta_prev_position = prev_velocity;
			delta_prev_positionF = prev_velocityF;
	
			delta_prev_velocity.x = 0.0f;
			delta_prev_velocity.y = 0.0f;
			Vector3 e = (secondVert.m_position - firstVert.m_position);
			e.Normalize();
			Vector3 Fk = -m_stiffness*((secondVert.m_position - firstVert.m_position).CalcLength() - m_stringLength) * e;
			Vector3 Fc = -m_cofficient * (DotProduct(e, (secondVert.m_velocity - firstVert.m_velocity))) *e;
			Vector3 A = Fk + Fc;// -secondVert.m_mass*m_gravityVector - m_stringCofficient*secondVert.m_velocity;
	
			Vector3 eF = (firstVert.m_position - secondVert.m_position);
			eF.Normalize();
			Vector3 FkF = -1 * Fk;
			Vector3 FcF = -1 * Fc;
			Vector3 AF = FkF + FcF;// -firstVert.m_mass*m_gravityVector - m_stringCofficient*firstVert.m_velocity;
	
			//delta_prev_velocity.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocity = A*deltaTime;
	
			next_position = prev_position + delta_prev_position;
			next_velocity = prev_velocity + delta_prev_velocity;
			if (secondVert.m_isPinned==false)
			{
				forces[(i + 1)*m_col + j] += A;
				//m_verts[(i + 1)*m_col + j].m_position = next_position;
				//m_verts[(i + 1)*m_col + j].m_velocity = next_velocity;
			}
			
	
			delta_prev_velocityF.z = -m_gravityVector.z*deltaTime;
			delta_prev_velocityF = AF*deltaTime;
			next_positionF = prev_positionF + delta_prev_positionF;
			next_velocityF = prev_velocityF + delta_prev_velocityF;
			if (firstVert.m_isPinned == false)
			{
				forces[i*m_col + j] += AF;
				//m_verts[i*m_col + j].m_position = next_positionF;
				//m_verts[i*m_col + j].m_velocity = next_velocityF;
			}
	
			renderer->DrawLineSegment(firstVert.m_position, secondVert.m_position, RGBA(1.0F, 0.0F, 1.0F), 1);
		}
	}
	
	for (int i = 0; i < m_row*m_col; i++)
	{
		Vector3 prev_position = m_verts[i].m_position;
		Vector3 prev_velocity = m_verts[i].m_velocity;

		Vector3 next_position;
		Vector3 next_velocity;

		Vector3 delta_prev_position = Vector3(0.0f,0.0f,0.0f);
		Vector3 delta_prev_velocity = Vector3(0.0f, 0.0f, 0.0f);

		if (m_verts[i].m_isPinned==false)
		{
			delta_prev_velocity = (forces[i] - m_verts[i].m_mass*m_gravityVector - m_stringCofficient*m_verts[i].m_velocity)*deltaTime;
			delta_prev_position = prev_velocity *deltaTime;
		}
		

		next_position = prev_position + delta_prev_position;
		next_velocity = prev_velocity + delta_prev_velocity;
		m_verts[i].m_position = next_position;
		m_verts[i].m_velocity = next_velocity;
	}

	//left -> right
	for (int k = 0; k < 2; k++)
	{

		for (int j = 0; j < m_col; j++)
		{
			for (int i = 0; i < m_row - 1; i++)
			{
				StringVerts firstVert = m_verts[j*m_row + i];
				StringVerts secondVert = m_verts[j*m_row + i + 1];

				Vector3 delta = secondVert.m_position - firstVert.m_position;
				float deltaLength = delta.CalcLength();
				float diff = (deltaLength - m_stringLength) / deltaLength;
				constraints[j*m_row + i] += delta*0.1f*diff;
				constraints[j*m_row + i + 1] -= delta*0.1f*diff;
				if (secondVert.m_isPinned == true)
				{
					constraints[j*m_row + i + 1] = Vector3(0.0f, 0.0f, 0.0f);
				}
				if (firstVert.m_isPinned == true)
				{
					constraints[j*m_row + i] = Vector3(0.0f, 0.0f, 0.0f);
				}
			}
		}
		//
		//top -> bot
		for (int i = 0; i < m_row - 1; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				StringVerts firstVert = m_verts[i*m_col + j];
				StringVerts secondVert = m_verts[(i + 1)*m_col + j];

				Vector3 delta = secondVert.m_position - firstVert.m_position;
				float deltaLength = delta.CalcLength();
				float diff = (deltaLength - m_stringLength) / deltaLength;
				constraints[i*m_col + j] += delta*0.1f*diff;
				constraints[(i + 1)*m_col + j] -= delta*0.1f*diff;
				if (firstVert.m_isPinned == true)
				{
					constraints[i*m_col + j] = Vector3(0.0f, 0.0f, 0.0f);
				}
				if (secondVert.m_isPinned == true)
				{
					constraints[(i + 1)*m_col + j] = Vector3(0.0f, 0.0f, 0.0f);
				}

			}
		}

		//top left -> bot right
		for (int i = 0; i < m_row - 1; i++)
		{
			for (int j = 0; j < m_col - 1; j++)
			{
				StringVerts firstVert = m_verts[i*m_col + j];
				StringVerts secondVert = m_verts[(i + 1)*m_col + j + 1];

				Vector3 delta = secondVert.m_position - firstVert.m_position;
				float deltaLength = delta.CalcLength();
				float diff = (deltaLength - m_stringLength*SQUAREROOT2) / deltaLength;
				constraints[i*m_col + j] += delta*0.1f*diff;
				constraints[(i + 1)*m_col + j + 1] -= delta*0.1f*diff;
				if (firstVert.m_isPinned == true)
				{
					constraints[i*m_col + j] = Vector3(0.0f, 0.0f, 0.0f);
				}
				if (secondVert.m_isPinned == true)
				{
					constraints[(i + 1)*m_col + j + 1] = Vector3(0.0f, 0.0f, 0.0f);
				}

			}
		}
		//
		//top right -> bot left
		for (int i = m_row - 1; i > 0; i--)
		{
			for (int j = 0; j < m_col - 1; j++)
			{
				StringVerts firstVert = m_verts[i*m_col + j];
				StringVerts secondVert = m_verts[(i - 1)*m_col + j + 1];

				Vector3 delta = secondVert.m_position - firstVert.m_position;
				float deltaLength = delta.CalcLength();
				float diff = (deltaLength - m_stringLength*SQUAREROOT2) / deltaLength;
				constraints[i*m_col + j] += delta*0.1f*diff;
				constraints[(i - 1)*m_col + j + 1] -= delta*0.1f*diff;
				if (firstVert.m_isPinned == true)
				{
					constraints[i*m_col + j] = Vector3(0.0f, 0.0f, 0.0f);
				}
				if (secondVert.m_isPinned == true)
				{
					constraints[(i - 1)*m_col + j + 1] = Vector3(0.0f, 0.0f, 0.0f);
				}

			}
		}

		for (int i = 0; i < m_row*m_col; i++)
		{
			m_verts[i].m_position += constraints[i];
			constraints[i] = Vector3(0.0,0.0,0.0);
		}
	}
	
}
NTBVertex3D_PCT* StringSystem::createTBN(int& size)
{
	RGBA color = RGBA(1.0f, 1.0f, 1.0f, 1.0f);
	Vector3 dontCare = Vector3(0.0f, 0.0f, 0.0f);
	NTBVertex3D_PCT* verts = new NTBVertex3D_PCT[m_col*m_row];
	for (int i = 0; i < m_row-1; i++)
	{
		for (int j = 0; j < m_col-1;j++)
		{
			verts[i*m_col * 6 + j * 6] = NTBVertex3D_PCT(m_verts[i*m_col + j].m_position, Vector2((float)i / m_col, (float)j / m_row), dontCare, dontCare, dontCare, color);
			verts[i*m_col * 6 + j * 6 + 1] = NTBVertex3D_PCT(m_verts[i*m_col + j + 1].m_position, Vector2((float)i / m_col, (float)(j + 1) / m_row), dontCare, dontCare, dontCare, color);
			verts[i*m_col * 6 + j * 6 + 2] = NTBVertex3D_PCT(m_verts[(i + 1)*m_col + j + 1].m_position, Vector2((float)(i + 1) / m_col, (float)(j + 1) / m_row), dontCare, dontCare, dontCare, color);
			verts[i*m_col * 6 + j * 6 + 3] = NTBVertex3D_PCT(m_verts[i*m_col + j].m_position, Vector2((float)i / m_col, (float)j / m_row), dontCare, dontCare, dontCare, color);
			verts[i*m_col * 6 + j * 6 + 4] = NTBVertex3D_PCT(m_verts[(i + 1)*m_col + j + 1].m_position, Vector2((float)(i + 1) / m_col, (float)(j + 1) / m_row), dontCare, dontCare, dontCare, color);
			verts[i*m_col * 6 + j * 6 + 5] = NTBVertex3D_PCT(m_verts[(i + 1)*m_col + j].m_position, Vector2((float)(i + 1) / m_col, (float)j / m_row), dontCare, dontCare, dontCare, color);

		}
	}
	size = m_col*m_row*6;
	return verts;
}
//////////////////////////////////////////////////////////////////////////
void StringSystem::Unpin()
{
	m_verts[0].m_isPinned = false;
	m_verts[m_verts.size() - 1].m_isPinned = false;
	m_verts[m_col - 1].m_isPinned = false;
	m_verts[(m_row - 1)*m_row].m_isPinned = false;
}