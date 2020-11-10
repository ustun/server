set @save_dbug=@@debug_dbug;
eval $create_statement;
if ($insert_statement)
{
  eval $insert_statement;
}
if ($insert_statement2)
{
  eval $insert_statement;
}
if ($create_statement2)
{
  eval $create_statement2;
}
if ($show_statement0)
{
  eval $show_statement0;
}

--echo # State before failure
--list_files_write_file $DATADIR.files.txt $DATADIR/test
--replace_result #p# #P# #sp# #SP#
--replace_regex /#sql-ib[1-9][0-9]*\.ibd\n//
--cat_file $DATADIR.files.txt
--remove_file $DATADIR.files.txt

if ($show_statement1)
{
  eval $show_statement1;
}

show create table t1;
--eval set @@debug_dbug= $debug_dbug
# accept all errors
--disable_abort_on_error
--replace_regex /#sqlx-[0-9a-f_]*/#sqlx-nnnn_nnnn/i
--eval $fail_statement
--enable_abort_on_error
--echo # State after failure
--replace_result #p# #p#
--list_files $datadir/test
show create table t1;
set session debug_dbug=@save_dbug;
