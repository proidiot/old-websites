#include "answer.h"

#include "badlist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define USER "user"
#define PASSWORD "bad_passw0rd"

int internal_server_error(struct MHD_Connection* connection)
{
	const char* errorstr = "<html><body>An internal error has occured!"
		"</body></html>";

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(errorstr),
			(void*)errorstr,
			MHD_RESPMEM_PERSISTENT);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_INTERNAL_SERVER_ERROR,
				response);
		MHD_destroy_response(response);

		return ret;
	} else {
		return MHD_NO;
	}
}

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
		if (response == NULL) {
			return internal_server_error(connection);
		}
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	} else {
		const char* page = "<html><body>Unauthorized!</body></html>";
		int bad_count;

		const union MHD_ConnectionInfo* info = MHD_get_connection_info(
				connection,
				MHD_CONNECTION_INFO_CLIENT_ADDRESS);
		if (info == NULL) {
			return internal_server_error(connection);
		}
		bad_add((BADLIST)cls, info->client_addr);

		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
		if (response == NULL) {
			return internal_server_error(connection);
		}
		ret = MHD_queue_basic_auth_fail_response(
				connection,
				"Tutorial Example 5 Realm",
				response);
	}

	MHD_destroy_response(response);
	return ret;
}

