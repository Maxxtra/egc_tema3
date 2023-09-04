#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 point_light_pos[8];
uniform vec3 point_light_dir[8];
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 object_color;

uniform int is_spot_light;
uniform float angle;

out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(point_light_pos[0] - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect (-L, N));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light = 0.25 * material_kd;
	float diffuse_light = material_kd * max(dot(N, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
	}

	// TODO: compute light
	float light = ambient_light;
	float cut_off = angle;
	float spot_light = dot(-L, point_light_dir[0]);
	float spot_light_limit = cos(cut_off);
	float dist = distance(point_light_pos[0], world_position);
	float factor_attenuation = 1 / (pow(dist, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} 

	} else {
		light = ambient_light + factor_attenuation * (diffuse_light + specular_light);
	}



	vec3 N1 = normalize(world_normal);
	vec3 L1 = normalize(point_light_pos[1] - world_position);
	vec3 V1 = normalize(eye_position - world_position);
	vec3 H1 = normalize(L1 + V1);
	vec3 R1 = normalize(reflect (-L1, N1));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light1 = 0.25 * material_kd;
	float diffuse_light1 = material_kd * max(dot(N1, L1), 0);
	float specular_light1 = 0;

	if (diffuse_light > 0)
	{
		specular_light1 = material_ks * pow(max(dot(V1, R1), 0), material_shininess);
	}

	// TODO: compute light
	float light1 = ambient_light1;
	float cut_off1 = angle;
	float spot_light1 = dot(-L1, point_light_dir[1]);
	float spot_light_limit1 = cos(cut_off1);
	float dist1 = distance(point_light_pos[1], world_position);
	float factor_attenuation1 = 1 / (pow(dist1, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att1 = (spot_light1 - spot_light_limit1) / (1.0f - spot_light_limit1);
			float light_att_factor1 = pow(linear_att1, 2);
			light1 = ambient_light1 + light_att_factor1 * (diffuse_light1 + specular_light1);
		} 

	} else {
		light1 = ambient_light1 + factor_attenuation1 * (diffuse_light1 + specular_light1);
	}

	vec3 N2 = normalize(world_normal);
	vec3 L2 = normalize(point_light_pos[2] - world_position);
	vec3 V2 = normalize(eye_position - world_position);
	vec3 H2 = normalize(L2 + V2);
	vec3 R2 = normalize(reflect (-L2, N2));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light2 = 0.25 * material_kd;
	float diffuse_light2 = material_kd * max(dot(N2, L2), 0);
	float specular_light2 = 0;

	if (diffuse_light > 0)
	{
		specular_light2 = material_ks * pow(max(dot(V2, R2), 0), material_shininess);
	}

	// TODO: compute light
	float light2 = ambient_light2;
	float cut_off2 = angle;
	float spot_light2 = dot(-L2, point_light_dir[2]);
	float spot_light_limit2 = cos(cut_off2);
	float dist2 = distance(point_light_pos[2], world_position);
	float factor_attenuation2 = 1 / (pow(dist2, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att2 = (spot_light2 - spot_light_limit2) / (1.0f - spot_light_limit2);
			float light_att_factor2 = pow(linear_att2, 2);
			light2 = ambient_light2 + light_att_factor2 * (diffuse_light2 + specular_light2);
		} 

	} else {
		light2 = ambient_light2 + factor_attenuation2 * (diffuse_light2 + specular_light2);
	}


	vec3 N3 = normalize(world_normal);
	vec3 L3 = normalize(point_light_pos[3] - world_position);
	vec3 V3 = normalize(eye_position - world_position);
	vec3 H3 = normalize(L3 + V3);
	vec3 R3 = normalize(reflect (-L3, N3));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light3 = 0.25 * material_kd;
	float diffuse_light3 = material_kd * max(dot(N3, L3), 0);
	float specular_light3 = 0;

	if (diffuse_light > 0)
	{
		specular_light3 = material_ks * pow(max(dot(V3, R3), 0), material_shininess);
	}

	// TODO: compute light
	float light3 = ambient_light3;
	float cut_off3 = angle;
	float spot_light3 = dot(-L3, point_light_dir[3]);
	float spot_light_limit3 = cos(cut_off3);
	float dist3 = distance(point_light_pos[3], world_position);
	float factor_attenuation3 = 1 / (pow(dist3, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att3 = (spot_light3 - spot_light_limit3) / (1.0f - spot_light_limit3);
			float light_att_factor3 = pow(linear_att3, 2);
			light3 = ambient_light3 + light_att_factor3 * (diffuse_light3 + specular_light3);
		} 

	} else {
		light3 = ambient_light3 + factor_attenuation3 * (diffuse_light3 + specular_light3);
	}

	vec3 N4 = normalize(world_normal);
	vec3 L4 = normalize(point_light_pos[4] - world_position);
	vec3 V4 = normalize(eye_position - world_position);
	vec3 H4 = normalize(L4 + V4);
	vec3 R4 = normalize(reflect (-L4, N4));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light4 = 0.25 * material_kd;
	float diffuse_light4 = material_kd * max(dot(N4, L4), 0);
	float specular_light4 = 0;

	if (diffuse_light > 0)
	{
		specular_light4 = material_ks * pow(max(dot(V4, R4), 0), material_shininess);
	}

	// TODO: compute light
	float light4 = ambient_light4;
	float cut_off4 = angle;
	float spot_light4 = dot(-L4, point_light_dir[4]);
	float spot_light_limit4 = cos(cut_off4);
	float dist4 = distance(point_light_pos[4], world_position);
	float factor_attenuation4 = 1 / (pow(dist4, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att4 = (spot_light4 - spot_light_limit4) / (1.0f - spot_light_limit4);
			float light_att_factor4 = pow(linear_att4, 2);
			light4 = ambient_light4 + light_att_factor4 * (diffuse_light4 + specular_light4);
		} 

	} else {
		light4 = ambient_light4 + factor_attenuation4 * (diffuse_light4 + specular_light4);
	}

	vec3 N5 = normalize(world_normal);
	vec3 L5 = normalize(point_light_pos[5] - world_position);
	vec3 V5 = normalize(eye_position - world_position);
	vec3 H5 = normalize(L5 + V5);
	vec3 R5 = normalize(reflect (-L5, N5));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light5 = 0.25 * material_kd;
	float diffuse_light5 = material_kd * max(dot(N5, L5), 0);
	float specular_light5 = 0;

	if (diffuse_light > 0)
	{
		specular_light5 = material_ks * pow(max(dot(V5, R5), 0), material_shininess);
	}

	// TODO: compute light
	float light5 = ambient_light5;
	float cut_off5 = angle;
	float spot_light5 = dot(-L5, point_light_dir[5]);
	float spot_light_limit5 = cos(cut_off5);
	float dist5 = distance(point_light_pos[5], world_position);
	float factor_attenuation5 = 1 / (pow(dist5, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att5 = (spot_light5 - spot_light_limit5) / (1.0f - spot_light_limit5);
			float light_att_factor5 = pow(linear_att5, 2);
			light5 = ambient_light5 + light_att_factor5 * (diffuse_light5 + specular_light5);
		} 

	} else {
		light5 = ambient_light5 + factor_attenuation5 * (diffuse_light5 + specular_light5);
	}
	
	vec3 N6 = normalize(world_normal);
	vec3 L6 = normalize(point_light_pos[6] - world_position);
	vec3 V6 = normalize(eye_position - world_position);
	vec3 H6 = normalize(L6 + V6);
	vec3 R6 = normalize(reflect (-L6, N6));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light6 = 0.25 * material_kd;
	float diffuse_light6 = material_kd * max(dot(N6, L6), 0);
	float specular_light6 = 0;

	if (diffuse_light > 0)
	{
		specular_light6 = material_ks * pow(max(dot(V6, R6), 0), material_shininess);
	}

	// TODO: compute light
	float light6 = ambient_light6;
	float cut_off6 = angle;
	float spot_light6 = dot(-L6, point_light_dir[6]);
	float spot_light_limit6 = cos(cut_off6);
	float dist6 = distance(point_light_pos[6], world_position);
	float factor_attenuation6 = 1 / (pow(dist6, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att6 = (spot_light6 - spot_light_limit6) / (1.0f - spot_light_limit6);
			float light_att_factor6 = pow(linear_att6, 2);
			light6 = ambient_light6 + light_att_factor6 * (diffuse_light6 + specular_light6);
		} 

	} else {
		light6 = ambient_light6 + factor_attenuation6 * (diffuse_light6 + specular_light6);
	}

	vec3 N7 = normalize(world_normal);
	vec3 L7 = normalize(point_light_pos[7] - world_position);
	vec3 V7 = normalize(eye_position - world_position);
	vec3 H7 = normalize(L7 + V7);
	vec3 R7 = normalize(reflect (-L7, N7));

	// TODO: define ambient light component, compute diffuse light componen, specular light component
	float ambient_light7 = 0.25 * material_kd;
	float diffuse_light7= material_kd * max(dot(N7, L7), 0);
	float specular_light7 = 0;

	if (diffuse_light > 0)
	{
		specular_light7 = material_ks * pow(max(dot(V7, R7), 0), material_shininess);
	}

	// TODO: compute light
	float light7 = ambient_light7;
	float cut_off7 = angle;
	float spot_light7 = dot(-L7, point_light_dir[7]);
	float spot_light_limit7 = cos(cut_off7);
	float dist7 = distance(point_light_pos[7], world_position);
	float factor_attenuation7 = 1 / (pow(dist7, 2) + 1);
	
	if (is_spot_light == 1) {

		if (spot_light > spot_light_limit) {	 
			
			float linear_att7 = (spot_light7 - spot_light_limit7) / (1.0f - spot_light_limit7);
			float light_att_factor7 = pow(linear_att7, 2);
			light7 = ambient_light7 + light_att_factor7 * (diffuse_light7 + specular_light7);
		} 

	} else {
		light7 = ambient_light7 + factor_attenuation7 * (diffuse_light7 + specular_light7);
	}

	// TODO: write pixel out color
	vec3 colour = object_color * light + object_color * light1 + object_color * light2 + object_color * light3 + object_color * light4 + object_color * light5 + 
	object_color * light6;

	out_color = vec4(colour, 1.f);
}