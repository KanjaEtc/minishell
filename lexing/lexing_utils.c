int	update_quote_status(char c, int curr_status)
{
	if (curr_status == 0 && (c == '\'' || c == ""))
		return (c);
	else if (curr_status)
		return (0);
	return (curr_status);
}

int	unclosed_quote(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (line[i])
	{
		status = update_quote_status(line[i], status);
		i++;
	}

	if (status != 0)
		return (1); //ca veut dire qu'il reste une quote non fermee
	return (0);
}