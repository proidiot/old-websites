#include "answer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define USER "user"
#define PASSWORD "bad_passw0rd"

int answer_to_connection(
		void* cls,
		struct MHD_Connection* connection,
		const char* url,
		const char* method,
		const char* version,
		const char* upload_data,
		size_t* upload_data_size,
		void** con_cls)
{
	char* user;
	char* pass;
	int authorized;
	struct MHD_Response* response;
	int ret;

	if (strncmp(method, "GET", 4) != 0) {
		return MHD_NO;
	}

	if (*con_cls == NULL) {
		*con_cls = connection;
		return MHD_YES;
	}

	pass = NULL;
	user = MHD_basic_auth_get_username_password(connection, &pass);
	authorized = (user != NULL)
		&& (strncmp(user, USER, strlen(USER)) == 0)
		&& (strncmp(pass, PASSWORD, strlen(PASSWORD)) == 0);
	if (user != NULL) {
		free(user);
	}
	if (pass != NULL) {
		free(pass);
	}

	if (authorized) {
		const char* page = "<html><body>Authorized!</body></html>";
		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	} else {
		const char* page = "<html><body>Unauthorized!</body></html>";
		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
		ret = MHD_queue_basic_auth_fail_response(
				connection,
				"Tutorial Example 5 Realm",
				response);
	}

	MHD_destroy_response(response);
	return ret;
}

